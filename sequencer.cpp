/**
 * Author : Balaji Chandrasekaran
 * ASU ID: 1208948451
 */
extern "C"{
#include "compiler.h"
}

#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>

#define ALLOC(node) (node*) calloc(1, sizeof(node))

using namespace::std;

static int bodyflag = 0;

map<string,ValueNode*> global_values;

static int ifdepth;


struct StatementNode* parse_generate_intermediate_representation();
struct ValueNode* parse_valueNode();
struct AssignmentStatement* parse_assign_stmt();
struct PrintStatement* parse_print_stmt();
struct IfStatement* parse_if_stmt();

vector<StatementNode*> tracknestedif;

//*****************function for parsing switch statement in the main ****************
struct IfStatement* parse_generate_case_representation(ValueNode* CO1,int caseOrDefault)
{
    ValueNode* CO2;
    if(caseOrDefault==CASE)
    {
        ttype=getToken();
        if (ttype!=NUM)
        {
            return NULL;
        }
        ungetToken();
        CO2=parse_valueNode();
    }
    else
    {
        CO2=CO1;
    }
    IfStatement* if_stmt = ALLOC(struct IfStatement);
    if_stmt->condition_operand1=CO1;
    if_stmt->condition_op=NOTEQUAL;
    if_stmt->condition_operand2=CO2;
    ttype=getToken();
    if (ttype!=COLON)
    {
        return NULL;
    }
    ttype=getToken();
    if(ttype!=LBRACE)
    {
        return NULL;
    }

    StatementNode* false_stmt_node=ALLOC(struct StatementNode);
    false_stmt_node->type=NOOP_STMT;
    false_stmt_node->next=parse_generate_intermediate_representation();
    if_stmt->false_branch=false_stmt_node;
    return if_stmt;

}

StatementNode* findbefore;
StatementNode* gotstmt = ALLOC(struct StatementNode);

struct StatementNode* parse_switch_stmt()
{
	vector<StatementNode*> temp;
	int flag = 0;
	int vector_size = 0;

    StatementNode* switchStmt;


    ValueNode* ifOperand1;

    //condition_operand1
    ttype = getToken();
    if (ttype == ID)
    {
    	flag = 1;
        ifOperand1 = global_values[token];
    }

    if(flag == 0)
    {
        return NULL;
    }

    ttype=getToken();

    if (ttype != LBRACE)
    {
        return NULL;
    }

    ttype = getToken();

    if (ttype != CASE)
    {
        return NULL;
    }

    StatementNode* true_stmt_node=NULL;
    StatementNode* terminalNode;
    StatementNode* terminalNode1;



    int firstCase = 1;
    int flt = 0;


    gotstmt->type = GOTO_STMT;
    gotstmt->goto_stmt = ALLOC(struct GotoStatement);

    do{
    	cout<<"\nzzzzzz "<<ttype;
        IfStatement* caseStmt = parse_generate_case_representation(ifOperand1,ttype);

        //first case ku checking

        if (firstCase)
        {
        	cout<<"\ncome only once "<<ttype;
            firstCase = 0;
            StatementNode* firstCase = ALLOC(struct StatementNode);
            firstCase->type = IF_STMT;
            firstCase->if_stmt = caseStmt;
            switchStmt = firstCase;
            findbefore = firstCase;
            flt = 1;
        }
        else if(firstCase == 0)
        {
        	cout<<"\ncome two times "<<ttype;
        	true_stmt_node = ALLOC(struct StatementNode);
        	true_stmt_node->type = IF_STMT;
        	true_stmt_node->if_stmt = caseStmt;
        	if(flt == 1)
        	{
            	while(findbefore->next != NULL)
            	{
            		findbefore = findbefore->next;
            	}
            	findbefore->if_stmt->true_branch = true_stmt_node;
            	flt = 0;
        	}
        	else
        	{
				findbefore = switchStmt;
				while(findbefore->next != NULL)
				{
					findbefore = findbefore->next;
				}
				findbefore->if_stmt->true_branch = true_stmt_node;
        	}
        }

        terminalNode = caseStmt->false_branch;
        while (terminalNode->next != NULL)
        {
            terminalNode=terminalNode->next;
        }

        temp.push_back(terminalNode);
        ttype=getToken();
    }while (ttype==CASE||ttype==DEFAULT);



    terminalNode1 = switchStmt;
    while (terminalNode1->next != NULL)
    {
        terminalNode1=terminalNode1->next;
    }


    gotstmt->goto_stmt->target = terminalNode;

    vector_size = temp.size();
    for(int i = 0; i < vector_size ; i++)
    {
    	temp[i]->next = gotstmt;
    }

//    if (terminalNode)
//    {
//        stmt_list.push_back(terminalNode);
//        stmt_list.push_back(true_stmt_node);
//    }
    ungetToken();
    return switchStmt;
}

struct AssignmentStatement* parse_assign_stmt()
{
	int fg = 0;
	int fg1 = 0;
    AssignmentStatement* assignStmtNode = ALLOC(struct AssignmentStatement);

    if (ttype == ID)
    {
    	if(global_values[token] == NULL)
    	{
        assignStmtNode->left_hand_side = parse_valueNode();
        global_values[assignStmtNode->left_hand_side->name] = assignStmtNode->left_hand_side;
    	}
    	else
    	{
            getToken();
            assignStmtNode->left_hand_side = global_values[token];
    	}
    }

    ttype = getToken();
    if (ttype != EQUAL)
    {
        return NULL;
    }

    ttype = getToken();
    if (ttype == NUM)
    {
    	fg = 1;
        ungetToken();
        assignStmtNode->operand1 = parse_valueNode();
    }

    if (ttype == ID && fg == 0)
    {
    	fg = 1;
    	if(global_values[token] == NULL)
    	{
            ungetToken();
            assignStmtNode->operand1 = parse_valueNode();
    	}
    	else
    	{
    		assignStmtNode->operand1 = global_values[token];
    	}
    }
    else if(fg == 0)
    {
        return NULL;
    }

//    if (ttype == NUM || (ttype == ID && global_values[token] == NULL))
//    {
//        ungetToken();
//        assignStmtNode->operand1 = parse_valueNode();
//    }
//    else if (ttype == ID)
//    {
//        assignStmtNode->operand1 = global_values[token];
//    }
//    else
//    {
//        return NULL;
//    }

    ttype = getToken();

    if (ttype == SEMICOLON)
    {
        assignStmtNode->op = 0;
        assignStmtNode->operand2 = NULL;

        return assignStmtNode;
    }

    if (ttype == PLUS)
    {
		assignStmtNode->op = PLUS;
    }
    else if(ttype == MINUS)
    {
		assignStmtNode->op = MINUS;
    }
    else if(ttype == MULT)
    {
		assignStmtNode->op = MULT;
    }
    else if(ttype == DIV)
    {
		assignStmtNode->op = DIV;
    }
    else
    {
		//invalid
		return NULL;
    }


    ttype = getToken();
    if (ttype == NUM)
    {
    	fg1 = 1;
        ungetToken();
        assignStmtNode->operand2 = parse_valueNode();
    }

    if (ttype == ID && fg1 == 0)
    {
    	fg1 = 1;
    	if(global_values[token] == NULL)
    	{
            ungetToken();
            assignStmtNode->operand2 = parse_valueNode();
    	}
    	else
    	{
    		assignStmtNode->operand2 = global_values[token];
    	}
    }
    else if(fg1 == 0)
    {
        return NULL;
    }
//
//    if (ttype == NUM || (ttype == ID && global_values[token] == NULL))
//    {
//        ungetToken();
//        assignStmtNode->operand2 = parse_valueNode();
//    }
//    else if (ttype == ID)
//    {
//        assignStmtNode->operand2 = global_values[token];
//    }
//    else
//    {
//        return NULL;
//    }

    ttype = getToken();

    if (ttype == SEMICOLON)
    {
        return assignStmtNode;
    }
    else
    {
        return NULL;
    }
}

struct PrintStatement* parse_print_stmt()
{
	int fg = 0;
    PrintStatement* print_stmt = ALLOC(struct PrintStatement);

    ttype = getToken();

    if (ttype == NUM)
    {
    	fg = 1;
        ungetToken();
        print_stmt->id = parse_valueNode();
    }

    if (ttype == ID && fg == 0)
    {
    	fg = 1;
    	if(global_values[token] == NULL)
    	{
            ungetToken();
            print_stmt->id = parse_valueNode();
    	}
    	else
    	{
    		print_stmt->id = global_values[token];
    	}
    }
    else if(fg == 0)
    {
        return NULL;
    }

//    if (ttype==NUM || (ttype==ID && global_values[token]==NULL))
//    {
//        ungetToken();
//        print_stmt->id = parse_valueNode();
//    }
//    else if (ttype==ID)
//    {
//        print_stmt->id = global_values[token];
//    }
//    else
//    {
//        return NULL;
//    }
    //parse_generate_value_representation();

    ttype = getToken();

    if (ttype != SEMICOLON)
    {
        return NULL;
    }
    else
    {
    	return print_stmt;
    }
}


//*****************function for parsing if statement in the main ****************
struct IfStatement* parse_if_stmt()
{
	int f1 = 0;
	int f2 = 0;
	IfStatement* ifStmt = ALLOC(struct IfStatement);

	++ifdepth;

    //condition_operand1
	ttype = getToken();

    if (ttype == NUM)
    {
    	f1 = 1;
        ungetToken();
        ifStmt->condition_operand1 = parse_valueNode();
    }

    if (ttype == ID && f1 == 0)
    {
    	f1 = 1;
    	if(global_values[token] == NULL)
    	{
            ungetToken();
            ifStmt->condition_operand1 = parse_valueNode();
    	}
    	else
    	{
    		ifStmt->condition_operand1 = global_values[token];
    	}
    }
    else if(f1 == 0)
    {
        return NULL;
    }

    //condition_op
    ttype = getToken();

    if (ttype == GREATER)
    {
		ifStmt->condition_op = GREATER;
    }
    else if (ttype == LESS)
    {
		ifStmt->condition_op = LESS;
    }
    else if (ttype == NOTEQUAL)
    {
		ifStmt->condition_op = NOTEQUAL;
    }
    else
    {
		return NULL;
    }

    //for operand 2

    ttype = getToken();

    if (ttype == NUM)
    {
    	f2 = 1;
        ungetToken();
        ifStmt->condition_operand2 = parse_valueNode();
    }

    if (ttype == ID && f2 == 0)
    {
    	f2 = 1;
    	if(global_values[token] == NULL)
    	{
            ungetToken();
            ifStmt->condition_operand2 = parse_valueNode();
    	}
    	else
    	{
    		ifStmt->condition_operand2 = global_values[token];
    	}
    }
    else if(f2 == 0)
    {
        return NULL;
    }

    //body syntax
    ttype = getToken();

    if (ttype != LBRACE)
    {
        return NULL;
    }

    ifStmt->true_branch = parse_generate_intermediate_representation();
//    cout<<"\n &&&&&&&after true branch";

    StatementNode* endStmtNode = ALLOC(struct StatementNode);
    StatementNode* findEndNode;

    endStmtNode->type = NOOP_STMT;
    ifStmt->false_branch = endStmtNode;

    findEndNode = ifStmt->true_branch;

    for (;findEndNode->next != NULL;)
    {
        findEndNode = findEndNode->next;
    }

    findEndNode->next = endStmtNode;

    if (ifdepth > 0)
    {
        tracknestedif.push_back(endStmtNode);
    }
    else if(ifdepth <= 0)
    {
//    	cout<<"\n (((((((((coming here once)))))))))))";
        endStmtNode->next = parse_generate_intermediate_representation();
    }

    --ifdepth;

    return ifStmt;
}


//flags for the functions to be used in main function.
//static int flag;
//static int flag2;
struct ValueNode* parse_valueNode()
{
    ValueNode *valueN = ALLOC(struct ValueNode);

    valueN->value = 0;

    ttype = getToken();

    int flr = 0;

    if (ttype == ID)
    {
    	flr = 1;
        valueN->name = strdup(token);
    }
    if (ttype == NUM && flr == 0)
    {
    	flr = 1;
        valueN->value = atoi(token);
    }
    if(flr == 0)
    {
        return NULL;
    }

    return valueN;
}


// The function that is called in the main.
struct StatementNode* parse_generate_intermediate_representation()
{

     StatementNode* gotoStmtWhile = NULL;

     StatementNode* endNode = NULL;
	 //cout<<"inside function";
	 int flag = 0;
	 int flag2 = 0;


	StatementNode* node = ALLOC(struct StatementNode);

    while (((tracknestedif.empty()) == false))
    {
//    	cout<<"\n inside the while value of ttype at start "<<ttype;
    	StatementNode* stmt_prim = tracknestedif.back();
    	if(ttype != -1)
    		stmt_prim->next = node;
    	else
    		stmt_prim->next = NULL;
        tracknestedif.pop_back();
    }


	int traverseRbrace = 0;



    ttype = getToken();

//    cout<<"\n value of ttype at start "<<ttype;

    if (bodyflag == 0)
    {
//    	cout<<"\n come in only once ";
    	flag = 1;
        ifdepth = -1;
    	for ( ; ttype != LBRACE; ttype = getToken());
    }

    if(flag == 1)
    {
//    	cout<<" \n come in only once ";
        ttype = getToken();
        bodyflag = 1;
    }

    if (ttype == ID)
    {
		//cout<<" \n hai assign\n";
		ungetToken();
		node->type = ASSIGN_STMT;
		node->assign_stmt = parse_assign_stmt();
    }
    else if(ttype == PRINT)
    {
    	cout<<"come three times";
		node->type = PRINT_STMT;
		node->print_stmt = parse_print_stmt();
    }
    else if(ttype == IF)
    {
		//cout<<"\n hai if statement\n";
		node->type = IF_STMT;
		node->if_stmt = parse_if_stmt();
//            cout<<" \n *********%%%after first if end";
    }
    else if(ttype == WHILE)
    {
		node->type = IF_STMT;
		node->if_stmt = parse_if_stmt();
		endNode = node->if_stmt->true_branch;

		for (;endNode->next->type != NOOP_STMT; endNode = endNode->next);

		if(endNode->next->type == NOOP_STMT)
		{
			gotoStmtWhile = ALLOC(struct StatementNode);
			gotoStmtWhile->goto_stmt = ALLOC(struct GotoStatement);

			gotoStmtWhile->goto_stmt->target = node;
			gotoStmtWhile->type = GOTO_STMT;


			endNode->next = gotoStmtWhile;
		}
		else
			cout<<"check for fatal error";
    }
    else if(ttype == SWITCH)
    {
    	node = parse_switch_stmt();
    }
    else
    {
//            case SWITCH:
////              	cout<<" \n hai";
//                stmtNode = parse_switch_stmt();
//                break;
//    	  	  cout<<"\n come here at last "<<ttype;
		return NULL;
    }



    ttype = getToken();

    if (ttype == RBRACE)
    {
//    	cout<<"\n**********number of times******";
    	flag2 = 1;
        traverseRbrace = 0;
        while(1)
        {
        	ttype = getToken();
//        	cout<<"\n num of braces : \n"<<ttype;
            traverseRbrace = 1;
        	if(ttype == RBRACE)
        		continue;
        	else
        		break;
        }
//    	cout<<"\n come here"<<ttype;
    	ungetToken();
//    	cout<<"\n come here when ungettoken() = "<<ttype;
    }

    if(flag2 == 1 && traverseRbrace == 1)
    {

    	flag2 = 0;
    	traverseRbrace = 0;
        return node;
    }

//    cout<<"\n token type "<<ttype;
    if (ttype != -1)
    {
        ungetToken();
        node->next=parse_generate_intermediate_representation();
    }
//    else
//    	cout<<" \n zzzzzzzzzzz dont fuck up ";

    return node;
}
