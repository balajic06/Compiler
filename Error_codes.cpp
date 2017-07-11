/*
 * Error_codes.cpp
 *
 *  Created on: Mar 22, 2016
 *      Author: Balaji Chandrasekaran
 */
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <stdio.h>
#include <stdlib.h>

extern "C"
{
#include "syntax.h"
}


int line_num = 0;

using namespace std;

int errf = 0;
int unkwn = 0;
map<string,string> mp;
vector<string> untypes;


vector< vector<string> > TYPE;
vector< vector<string> > VAR;


vector< vector<pair<string, string> > > bdy;
vector<pair<string, string> > tempbd;
stringstream st(stringstream::in | stringstream::out);

list<string> stmt_type;
list<int> linen;
vector<string> unkn;

void parse_Decl(struct declNode* dec);
void parse_type_decl_section(struct type_decl_sectionNode* typeDeclSection);
void parse_type_decl_list(struct type_decl_listNode* typeDeclList);
void parse_var_decl_section(struct var_decl_sectionNode* varDeclSection);
void parse_var_decl_list(struct var_decl_listNode* varDeclList);

vector<vector<string> > prinvec;


void parse_tree(struct programNode* prog)
{
	parse_Decl(prog->decl);
}
void parse_Decl(struct declNode* dec)
{
    if (dec->type_decl_section != NULL)
    {
        parse_type_decl_section(dec->type_decl_section);
    }
    if (dec->var_decl_section != NULL)
    {
        parse_var_decl_section(dec->var_decl_section);
    }
}

void parse_type_decl_section(struct type_decl_sectionNode* typeDeclSection)
{
	    if (typeDeclSection->type_decl_list != NULL)
	    {
	        parse_type_decl_list(typeDeclSection->type_decl_list);
	    }
}

void parse_type_decl_list(struct type_decl_listNode* typeDeclList)
{
	int flag = 0;
	struct type_decl_listNode* tempdecllist;
	tempdecllist = typeDeclList;
	struct type_declNode *temp;
	struct type_nameNode *tempname;
	struct id_listNode *tempid;
	vector<string> tempV;

	if(tempdecllist->type_decl != NULL)
	{
		line_num++;
		temp = tempdecllist->type_decl;
		tempname = temp->type_name;
		tempid = temp->id_list;
	}
	else
	{
		cout<<"some error in type section";
	}
	while(1)
	{
			if(tempname->type == 32)
			{
				tempV.push_back(tempname->id);
			}
			else if(tempname->type == 3)
			{
				tempV.push_back("INT");
			}
			else if(tempname->type == 4)
			{
				tempV.push_back("REAL");
			}
			else if(tempname->type == 5)
			{
				tempV.push_back("STRING");

			}
			else if(tempname->type == 6)
			{
				tempV.push_back("BOOLEAN");
			}
			else if(tempname->type == 8)
			{
				tempV.push_back("LONG");
			}
			else
			{
				break;
			}
			while(tempid != NULL)
			{
				flag = 1;
				tempV.push_back(tempid->id);
				tempid = tempid->id_list;
			}
			if(flag == 0)
			{
				break;
			}
			if(tempdecllist->type_decl_list != NULL)
			{
				tempdecllist = tempdecllist->type_decl_list;
				temp = tempdecllist->type_decl;
				tempname = temp->type_name;
				tempid = temp->id_list;
				TYPE.push_back(tempV);
				tempV.clear();
				line_num++;
			}
			else
			{
				line_num++;
				TYPE.push_back(tempV);
				break;
			}
	}
}

void parse_var_decl_section(struct var_decl_sectionNode* varDeclSection)
{
	    if (varDeclSection->var_decl_list != NULL)
	    {
	        parse_var_decl_list(varDeclSection->var_decl_list);
	    }
}

void parse_var_decl_list(struct var_decl_listNode* varDeclList)
{
	int flag = 0;
	struct var_decl_listNode* tempdecllist;
	tempdecllist = varDeclList;
	struct var_declNode *temp;
	struct type_nameNode *tempname;
	struct id_listNode *tempid;
	vector<string> tempV;

	if(tempdecllist->var_decl != NULL)
	{
		line_num++;
		temp = tempdecllist->var_decl;
		tempname = temp->type_name;
		tempid = temp->id_list;
	}
	else
	{
		cout<<"some error in type section";
	}
	while(1)
	{
			if(tempname->type == 32)
			{
				tempV.push_back(tempname->id);
			}
			else if(tempname->type == 3)
			{
				tempV.push_back("INT");
			}
			else if(tempname->type == 4)
			{
				tempV.push_back("REAL");
			}
			else if(tempname->type == 5)
			{
				tempV.push_back("STRING");

			}
			else if(tempname->type == 6)
			{
				tempV.push_back("BOOLEAN");
			}
			else if(tempname->type == 8)
			{
				tempV.push_back("LONG");
			}
			else
			{
				break;
			}
			while(tempid != NULL)
			{
				flag = 1;
				tempV.push_back(tempid->id);
				tempid = tempid->id_list;
			}
			if(flag == 0)
			{
				break;
			}
			if(tempdecllist->var_decl_list != NULL)
			{
				line_num++;
				tempdecllist = tempdecllist->var_decl_list;
				temp = tempdecllist->var_decl;
				tempname = temp->type_name;
				tempid = temp->id_list;
				VAR.push_back(tempV);
				tempV.clear();
			}
			else
			{
				line_num++;
				VAR.push_back(tempV);
				break;
			}
	}
}


void print_vector(vector< vector<string> > temp)
{
	vector<string> temp1;
	vector< vector<string> >::iterator i;
	vector<string>::iterator j;

	string type;
	for( i = temp.begin(); i != temp.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j ++)
		{
			if(j == temp1.begin())
			{
				type = (*j);
			}
			else
			{
				cout<<(*j)<< " ";
			}
		}
		cout<<" : "<< type<<"\n";
	}
}

//*************************************************************************************
// parsing body :-

void parse_stmt_list(struct stmt_listNode* stmt_list);
void parse_stmt(struct stmtNode* stmt);
void parse_assign_stmt(struct assign_stmtNode* assign_stmt);
void parse_expression_prefix(struct exprNode* expr);
void parse_while_stmt(struct while_stmtNode* while_stmt);
void parse_do_stmt(struct while_stmtNode* do_stmt);
void parse_condition(struct conditionNode* condition);
string Func_type(string str);

void parse_body(struct bodyNode* bd)
{
	parse_stmt_list(bd->stmt_list);
}

void parse_stmt_list(struct stmt_listNode* stmt_list)
{
    parse_stmt(stmt_list->stmt);
    if (stmt_list->stmt_list != NULL)
    {
        parse_stmt_list(stmt_list->stmt_list);
    }

}

void parse_stmt(struct stmtNode* stmt)
{
    switch (stmt->stmtType)
    {
        case ASSIGN:
        	stmt_type.push_back("ASSIGN");
        	linen.push_back(stmt->assign_stmt->lineno);
            parse_assign_stmt(stmt->assign_stmt);
            break;
        case 2:
        	stmt_type.push_back("COND");
        	linen.push_back(stmt->while_stmt->condition->lineno);
            parse_while_stmt(stmt->while_stmt);
            break;
        case 9:
        	linen.push_back(stmt->while_stmt->condition->lineno);
            parse_do_stmt(stmt->while_stmt);
            break;
//        case 11:
//            parse_switch_stmt(stmt->switch_stmt);
//            break;
    }
}

void parse_assign_stmt(struct assign_stmtNode* assign_stmt)
{
	string temp = Func_type(assign_stmt->id);
	pair<string,string> tempP = make_pair(assign_stmt->id, temp);
    tempbd.push_back(tempP);
    parse_expression_prefix(assign_stmt->expr);
    bdy.push_back(tempbd);
    tempbd.clear();
}

void parse_expression_prefix(struct exprNode* expr)
{
    if (expr->tag == EXPR)
    {
        parse_expression_prefix(expr->leftOperand);
        parse_expression_prefix(expr->rightOperand);
    }
    else if (expr->tag == PRIMARY)
    {
        if (expr->primary->tag == 32)
        {
        	string temp = Func_type(expr->primary->id);
        	pair<string, string> tempP = make_pair(expr->primary->id, temp);
            tempbd.push_back(tempP);
        }
        else if (expr->primary->tag == 33)
        {
        	st.str("");
        	st<<expr->primary->ival;
        	tempbd.push_back(make_pair(st.str(), "INT"));
        }
        else if (expr->primary->tag == 34)
        {
        	st.str("");
        	st<<expr->primary->fval;
        	string s = st.str();
        	s += "f";
        	tempbd.push_back(make_pair(s,"REAL"));
        }
    }
}

void parse_while_stmt(struct while_stmtNode* while_stmt)
{
    if(while_stmt->condition != NULL)
    {
    	parse_condition(while_stmt->condition);
        bdy.push_back(tempbd);
        tempbd.clear();
    }
    else
    {
    	cout<<"error in while printing";
    }
    parse_body(while_stmt->body);
}

void parse_do_stmt(struct while_stmtNode* do_stmt)
{
    parse_body(do_stmt->body);
    if(do_stmt->condition != NULL)
    {
    	stmt_type.push_back("COND");
    	parse_condition(do_stmt->condition);
        bdy.push_back(tempbd);
        tempbd.clear();
    }
    else
    {
    	cout<<"error in while printing";
    }
}

void parse_condition(struct conditionNode* condition)
{
	if(condition->left_operand != NULL)
	{
		if (condition->left_operand->tag == 32)
		{
        	string temp = Func_type(condition->left_operand->id);
        	pair<string, string> tempP = make_pair(condition->left_operand->id, temp);
			tempbd.push_back(tempP);
		}
		else if (condition->left_operand->tag== 33)
		{
			st.str("");
			st<<condition->left_operand->ival;
			tempbd.push_back(make_pair(st.str(), "INT"));
		}
		else if (condition->left_operand->tag == 34)
		{
			st.str("");
			st<<condition->left_operand->fval;
        	string s = st.str();
        	s += "f";
			tempbd.push_back(make_pair(s, "REAL"));
		}
	}
	else
	{
		cout<<"error in the condition";
	}
	if(condition->right_operand != NULL)
	{
		if (condition->right_operand->tag == 32)
		{
        	string temp = Func_type(condition->right_operand->id);
        	pair<string, string> tempP = make_pair(condition->right_operand->id, temp);
			tempbd.push_back(tempP);
		}
		else if (condition->right_operand->tag== 33)
		{
			st.str("");
			st<<condition->right_operand->ival;
			tempbd.push_back(make_pair(st.str(), "INT"));
		}
		else if (condition->right_operand->tag == 34)
		{
			st.str("");
			st<<condition->right_operand->fval;
        	string s = st.str();
        	s += "f";
			tempbd.push_back(make_pair(s, "REAL"));
		}
	}
}

void print_body_vector(vector< vector<pair<string,string> > > temp)
{
	pair<string, string> tpP;
	vector<pair<string,string> > temp1;
	vector< vector<pair<string, string> > >::iterator i;
	vector<pair<string, string> >::iterator j;
	list<string>::iterator it = stmt_type.begin();
	for( i = temp.begin(); i != temp.end(); i++)
	{
		if(it != stmt_type.end())
		{
			cout<<*it<< " -> ";
			it++;
		}
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j ++)
		{
			tpP = (*j);
			cout<<"( "<<tpP.first<<", "<<tpP.second<<" )"<<"  ";
		}
		cout<<"\n";
	}
}

string findtpvar(string t)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string t1,t2;
	for( i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j ++)
		{
			if(j != temp1.begin())
			{
				if(t.compare(*j) == 0)
				{
					t1 = *(temp1.begin());
					if(*(temp1.begin()) == "INT" ||*(temp1.begin()) == "STRING" ||*(temp1.begin()) == "LONG" ||*(temp1.begin()) == "REAL" ||*(temp1.begin()) == "BOOLEAN" )
						return *(temp1.begin());
					else
					{
						t2 = findtpvar(*(temp1.begin()));
						if(t2 == "")
							return t1;
						else
							return t2;
					}
				}
			}
		}
	}
	return "";
}
string Func_type(string str)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string start;
	for( i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j ++)
		{
			if(str.compare(*j) == 0)
			{
				start = findtpvar(*(temp1.begin()));
				if(start != "")
					return start;
				else
					return *(temp1.begin());
			}
		}
	}
	return "UNKNOWN";
}

//******************************************************************************
// ERROR_CODE CHECKING
		//ERROR_CODE 1.1


int checkfunc(string t)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	for(i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}

string error_Code_1a()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				check = *j;
				fl = checkfunc(*j);
				if(fl > 1)
					return *j;
				j++;
			}
		}
	}
	return "";
}



		//ERROR_CODE_1.2


int checkfunc2(string t,vector< vector<string > >::iterator tp )
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	for(i = tp; i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}

string error_Code_1b()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j != temp1.begin())
			{
				j++;
			}
			else
			{
				check = *j;
				fl = checkfunc2(*j, i);
				if(fl > 0)
					return *j;
				j++;
			}
		}
	}
	return "";
}

		//ERROR_CODE_1.3


int checkfunc3(string t)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}

int checkfunc3(string t,vector< vector<string > >::iterator tp)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	i = tp;
	i++;
	for(; i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}


string error_Code_1c()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j++)
		{
				check = *j;
				fl = checkfunc3(*j);
				if(fl > 0)
					return *j;
		}
	}
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j++)
		{
			if(j == temp1.begin())
			{
				check = *j;
				fl = checkfunc3(*j, i);
				if(fl > 0)
					return *j;
			}
		}
	}

	return "";
}

			//ERROR_CODE_1.4

int checkfunc4(string t)
{
	int fl = 0;
	pair<string, string> tpP;
	vector<pair<string,string> > temp1;
	vector< vector<pair<string, string> > >::iterator i;
	vector<pair<string, string> >::iterator j;

	for( i = bdy.begin(); i != bdy.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j++)
		{
			tpP = (*j);
			if(t.compare(tpP.first) == 0)
			{
				fl++;
			}
		}
	}
	return fl;
}

string error_Code_1d()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = TYPE.begin(); i != TYPE.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j++)
		{
				check = *j;
				fl = checkfunc4(*j);
				if(fl > 0)
					return *j;
		}
	}
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end(); j++)
		{
			if(j == temp1.begin())
			{
				check = *j;
				fl = checkfunc4(*j);
				if(fl > 0)
					return *j;
			}
		}
	}

	return "";
}

		// ERROR_CODE 2.1

int checkfunc5(string t)
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}

string error_Code_2a()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				check = *j;
				fl = checkfunc5(*j);
				if(fl > 1)
					return *j;
				j++;
			}
		}
	}
	return "";
}

				// ERROR_CODE 2.2

int checkfunc6(string t,vector< vector<string > >::iterator tp )
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	int fl = 0;
	i = tp;
	i++;
	for(; i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j != temp1.begin())
			{
				j++;
			}
			else
			{
				if(t.compare(*j) == 0)
				{
					fl++;
				}
				j++;
			}
		}
	}
	return fl;
}

string error_Code_2b()
{
	vector<string > temp1;
	vector< vector<string > >::iterator i;
	vector<string >::iterator j;
	string check;
	int fl = 0;
	for(i = VAR.begin(); i != VAR.end(); i++)
	{
		temp1 = (*i);
		for(j = temp1.begin(); j != temp1.end();)
		{
			if(j == temp1.begin())
			{
				j++;
			}
			else
			{
				check = *j;
				fl = checkfunc6(*j, i);
				if(fl > 0)
					return *j;
				j++;
			}
		}
	}
	return "";
}

//****************************************************************************
//TYPE CHECKING C1- C5


string checkty(string t)
{
	map<string,string>::iterator it;
	it = mp.find(t);
	if(it != mp.end())
	{
		return it->second;
	}
	return "";
}

void updext(string t, string m)
{
	string prevty;
	map<string, string>::iterator i;
	i = mp.begin();
	while(i != mp.end())
	{
		if(i->second == t)
		{
			mp[i->first] = m;
		}
		i++;
	}
}
void updatemp(string t, string m)
{
	string extype ;
	map<string, string>::iterator it;

	it = mp.find(t);
	extype = it->second;
	if(it!=mp.end())
	{
		mp[t] = m;
		updext(extype,m);
	}
	else
	{
		cout<<"fatal error";
	}
}


void calctype(vector<pair<string,string> > t, string t1, int n)
{
	vector<pair<string,string> >::iterator i;

	pair<string, string> temp;

	string lefttype = "";
	string righttype = "";
	string righttype1 = "";

	int vectorsize = t.size();


	int lt;
	int rt;
	int rt1;

	string leftop = "";
	string rghtop = "";
	string rghtop1 = "";

	i = t.begin();

	int singlecondf = 0;

	while(i != t.end())
	{
		if(t1 == "ASSIGN")
		{
			if(vectorsize >= 2)
			{
				if(i == t.begin())
				{
					temp = (*i);
					leftop = temp.first;
					lefttype = checkty(leftop);
					if(lefttype == "INT" ||lefttype == "BOOLEAN" ||lefttype == "STRING" ||lefttype == "LONG" ||lefttype == "REAL")
					{
						lt = 1;
					}
					else if(lefttype.compare(0,7,"UNKNOWN") == 0)
					{
						lt = 3;
					}
					else
					{
						lt = 2;
					}
				}
				else
				{
					if(rghtop == "")
					{
						temp = (*i);
						rghtop = temp.first;
						righttype = checkty(rghtop);
						if(righttype == "INT" ||righttype == "BOOLEAN" ||righttype == "STRING" ||righttype == "LONG" ||righttype == "REAL")
						{
							rt = 1;
						}
						else if(righttype.compare(0,7,"UNKNOWN") == 0)
						{
							rt = 3;
						}
						else
						{
							rt = 2;
						}
					}
					else
					{
						temp = (*i);
						rghtop1 = temp.first;
						righttype1 = checkty(rghtop1);
						if(righttype1 == "INT" ||righttype1 == "BOOLEAN" ||righttype1 == "STRING" ||righttype1 == "LONG" ||righttype1 == "REAL")
						{
							rt1 = 1;
						}
						else if(righttype1.compare(0,7,"UNKNOWN") == 0)
						{
							rt1 = 3;
						}
						else
						{
							rt1 = 2;
						}
						if(righttype != righttype1)
						{
							if( (rt == 1) && (rt1 == 1) )
							{
								errf = 1;
								cout<<"\nTYPE MISMATCH "<<n<<" C2";
								break;
							}
							else if((rt == 1) && (rt1 == 2))
							{
								updatemp(rghtop1,righttype );
								rt = 1;
							}
							else if((rt == 1) && (rt1 == 3))
							{
								updatemp(rghtop1,righttype );
								rt = 1;
							}
							else if((rt == 2) && (rt1 == 1))
							{
								updatemp(rghtop,righttype1 );
								rt = 1;
								righttype = righttype1;
								rghtop = rghtop1;
							}
							else if((rt == 2) && (rt1 == 2))
							{
								updatemp(rghtop,righttype1 );
								rt = 2;
								righttype = righttype1;
								rghtop = rghtop1;
							}
							else if((rt == 2) && (rt1 == 3))
							{
								updatemp(rghtop1,righttype );
								rt = 2;
							}
							else if((rt == 3) && (rt1 == 1))
							{
								updatemp(rghtop,righttype1);
								rt = 1;
								righttype = righttype1;
								rghtop = rghtop1;
							}
							else if((rt == 3) && (rt1 == 2))
							{
								updatemp(rghtop,righttype1 );
								rt = 2;
								righttype = righttype1;
								rghtop = rghtop1;
							}
							else if((rt == 3) && (rt1 == 3))
							{
								updatemp(rghtop,righttype1 );
								rt = 3;
								righttype = righttype1;
								rghtop = rghtop1;
							}
						}
					}
				}
			}
		}
		else if(t1 == "COND")
		{
			if(vectorsize == 1)
			{
				if(i == t.begin())
				{
					temp = (*i);
					leftop = temp.first;
					lefttype = checkty(leftop);
					if(lefttype == "INT" ||lefttype == "BOOLEAN" ||lefttype == "STRING" ||lefttype == "LONG" ||lefttype == "REAL")
					{

						lt = 1;
					}
					else if(lefttype.compare(0,7,"UNKNOWN") == 0)
					{
						lt = 3;
					}
					else
					{
						lt = 2;
					}
				}
				if(lt == 1 && lefttype != "BOOLEAN")
				{
					errf = 1;
					cout<<"\nTYPE MISMATCH "<<n<<" C4";
					break;
				}
				else
				{
					updatemp(leftop,"BOOLEAN" );
				}
			}
			else
			{
				singlecondf = 1;
				if(i == t.begin())
				{
					temp = (*i);
					leftop = temp.first;
					lefttype = checkty(leftop);
					if(lefttype == "INT" ||lefttype == "BOOLEAN" ||lefttype == "STRING" ||lefttype == "LONG" ||lefttype == "REAL")
					{
						lt = 1;
					}
					else if(lefttype.compare(0,7,"UNKNOWN") == 0)
					{
						lt = 3;
					}
					else
					{
						lt = 2;
					}
				}
				else
				{
					temp = (*i);
					rghtop = temp.first;
					righttype = checkty(rghtop);
					if(righttype == "INT" ||righttype == "BOOLEAN" ||righttype == "STRING" ||righttype == "LONG" ||righttype == "REAL")
					{
						rt = 1;
					}
					else if(righttype.compare(0,7,"UNKNOWN") == 0)
					{
						rt = 3;
					}
					else
					{
						rt = 2;
					}
				}
			}
		}
		i++;
	}
	if(lefttype != righttype && errf == 0)
	{
		if( (lt == 1) && (rt == 1))
		{
			errf = 1;
			if(singlecondf == 1)
				cout<<"\n"<<"TYPE MISMATCH "<<n<<" C3";
			else
				cout<<"\n"<<"TYPE MISMATCH "<<n<<" C1";
		}
		else if((lt == 1) && (rt == 2))
		{

			updatemp(rghtop,lefttype );
		}
		else if((lt == 1) && (rt == 3))
		{

			updatemp(rghtop,lefttype );
		}
		else if((lt == 2) && (rt == 1))
		{

			updatemp(leftop,righttype );
		}
		else if((lt == 2) && (rt == 2))
		{

			updatemp(leftop,righttype );
		}
		else if((lt == 2) && (rt == 3))
		{
			updatemp(rghtop,lefttype );
		}
		else if((lt == 3) && (rt == 1))
		{
			updatemp(leftop,righttype);
		}
		else if((lt == 3) && (rt == 2))
		{
			updatemp(leftop,righttype );
		}
		else if((lt == 3) && (rt == 3))
		{
			updatemp(leftop,righttype );
		}
	}
}

void printmp()
{
	map<string,string>::iterator i;
	for(i = mp.begin(); i != mp.end() ; i++)
	{
		cout<<" "<<i->first<<" - "<<i->second;
	}

}

void insertmp(string t, string p)
{
	map<string,string>::iterator i;
	i = mp.find(t);
	string type = "";
	if(i == mp.end())
	{
		if(p == "INT"||p == "BOOLEAN"|| p =="STRING"||p == "REAL" || p == "LONG")
		{
			mp.insert(pair<string, string>(t,p));
		}
		else if(p == "UNKNOWN")
		{
			unkn.push_back(t);
			st.str("");
			st<<unkwn;
			string temp = st.str();
			type += p;
			type += temp;
			mp.insert(pair<string, string>(t,type));
		}
		else
		{
			mp.insert(pair<string, string>(t,p));
		}
	}
}

void mkmap()
{
	vector<vector< pair<string,string > > >::iterator it;
	vector<pair<string,string> >::iterator ii;
	vector<pair<string, string> > v;
	pair<string,string> tm;
	for(it = bdy.begin(); it != bdy.end(); it++)
	{
		v = *it;
		for(ii = v.begin(); ii != v.end(); ii++)
		{
			tm = *ii;
			insertmp(tm.first,tm.second);
		}
		unkwn += 1;
	}
}



void typecheck()
{
	vector<pair<string,string> > temp1;
	int i;
	int size = bdy.size();
	int no;
	string stmttype;


	list<string>::iterator it = stmt_type.begin();
	list<int>::iterator n = linen.begin();


	for( i = 0; i <size && errf == 0; i++)
	{
		if(it != stmt_type.end())
		{
			stmttype = *it;
		}
		if(n != linen.end())
		{
			no = *n;
		}
		temp1 = bdy[i];
		calctype(temp1,stmttype,no);
		it++;
		n++;
	}
}

//***********************function to print*******************

//************* print vector creation from VAR functions***********************


// unknown type to unknown build
//************************************

vector<string> mdfydunkn; // only conatins unknows var in body

void printv();

void fpn(string r, string s)
{
	vector<vector<string> >::iterator it;
	vector<string>::iterator ij;
	vector<string> l;
	vector<string> v ;
	int in = 0;
	string k;
	int flag = 0;
	for(it = prinvec.begin();it != prinvec.end(); it++, in++)
	{
		l = *it;
		for(ij = l.begin(); ij != l.end(); ij++)
		{
			if(ij == l.begin() && (*ij == s))
			{

				flag = 1;
				l.push_back(r);
				break;
			}
		}
		prinvec[in] = l;
	}
	if(flag == 0)
	{
		v.push_back(s);
		v.push_back(r);
		prinvec.push_back(v);
		v.clear();
	}
}

// for types implicitly declared in body and which doesnt have a type
void adf1()
{
	vector<string>::iterator w;
	map<string,string>::iterator i;
	vector<string> v ;

	for(w = unkn.begin();w != unkn.end();w++)
	{
		i = mp.find(*w);
		v.clear();
		if(i != mp.end())
		{
			if((i->second).compare(0,7,"UNKNOWN") != 0)
			{
				v.push_back(i->second);
				v.push_back(i->first);
				prinvec.push_back(v);
			}
			else if((i->second).compare(0,7,"UNKNOWN") == 0)
			{
				fpn(i->first,i->second);
			}
			else
			{
				cout<<"check error";
			}
		}
		else
		{
			cout<<"check error";
		}
	}
}


//***************************print vec*******************
void printv()
{
	vector<string>::iterator i;
	for(i = unkn.begin();i != unkn.end();i++)
	{
		cout<<*i<<" ";
	}
}
void printvmd()
{
	vector<string>::iterator i;
	for(i = mdfydunkn.begin();i != mdfydunkn.end();i++)
	{
		cout<<*i<<" ";
	}
}

// implicit variables in body with unknown type

int alrdyin(string r)
{
	vector<string>::iterator it;
	for(it = unkn.begin(); it != unkn.end();it++)
	{
		if(*it == r)
		{
			return 0;
		}
	}
return 1;
}
void mkunkn()
{
	vector<vector< pair<string,string > > >::iterator it;
	vector<pair<string,string> >::iterator ii;
	vector<pair<string, string> > v;
	pair<string,string> tm;
	for(it = bdy.begin(); it != bdy.end(); it++)
	{
		v = *it;
		for(ii = v.begin(); ii != v.end(); ii++)
		{
			tm = *ii;
			if((tm.second).compare(0,7,"UNKNOWN")== 0)
			{
				if(alrdyin(tm.first))
					unkn.push_back(tm.first);
			}
		}
	}
}
// end

// mdifying unknwn after type check

void mdfyunkn()
{
	vector<string>::iterator it;
	map<string, string>::iterator i;
	string tp;
	for(it = unkn.begin();it!=unkn.end();)
	{
		i = mp.find(*it);
		if(i != mp.end())
			tp = i->second;
		else
			cout<<"fatal error";
		if(tp.compare(0,7,"UNKNOWN") == 0)
		{
			mdfydunkn.push_back(i->first);
			it = unkn.erase(it);
		}
		else
			it++;
	}
}
//end



// new creation of prinvect

int ff = 0;
string chktyp(vector<string> z)
{
	map<string,string>::iterator j;
	vector<string>::iterator p;
	string r;
	for(p = z.begin(); p != z.end(); p++)
	{
		if( p != z.begin())
		{
			j = mp.find(*p);
			if(j != mp.end())
			{
				ff = 1;
				return j->second;
			}
		}
	}
	return "";
}
string checktyp(vector<string> t)
{
	vector<string>::iterator p;

	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	int in = 0, jn = 0;
	string sp;
	string store = "";
	for(p = t.begin(); p != t.end(); p++)
	{
		sp = *p;
		for(it = VAR.begin();it != VAR.end();it++, in++)
		{
			i = *it;
			for(ij = i.begin();ij != i.end();ij++, jn++)
			{
				if(ij == i.begin() && (sp == *ij))
				{
					store = chktyp(i);
					if(ff == 1)
					{
						i.erase(i.begin());
						i.insert(i.begin(),store);
						VAR.erase(it);
						VAR.insert(it,i);
						return store;
					}
				}
			}
		}
	}
	return store;
}

string fnint(string t)
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	string tp = "";
	for(it = TYPE.begin(); it != TYPE.end() ; it++)
	{
		i = *it;
		for(ij = i.begin(); ij != i.end(); ij++)
		{
			if(ij == i.begin())
				tp = *ij;
			if(ij != i.begin() && (t.compare(*ij)==0))
			{
				return tp;
			}
		}
	}
	return "";
}
void modifytypesec()
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	int in = 0, jn = 0;
	string tmp;
	for(it = TYPE.begin();it != TYPE.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && !(*ij == "REAL" || *ij == "BOOLEAN" || *ij == "INT" || *ij == "LONG"|| *ij == "STRING"))
			{
				tmp = checktyp(i);
				if(tmp != "")
				{
					i.erase(i.begin());
					i.insert(i.begin(),tmp);
					TYPE.erase(it);
					TYPE.insert(it,i);
					break;
				}
				else
				{
					tmp = fnint(*ij);
					if(tmp != "")
					{
						i.erase(i.begin());
						i.insert(i.begin(),tmp);
						TYPE.erase(it);
						TYPE.insert(it,i);
						break;
					}
				}
			}
		}

	}

}

void modifyvarsec()
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	int in = 0, jn = 0;
	string tmp;
	for(it = VAR.begin();it != VAR.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && !(*ij == "REAL" || *ij == "BOOLEAN" || *ij == "INT" || *ij == "LONG"|| *ij == "STRING"))
			{
				tmp = findtpvar(*ij);
				if(tmp != "" && (tmp != *ij))
				{
					i.erase(i.begin());
					i.insert(i.begin(),tmp);
					VAR.erase(it);
					VAR.insert(it,i);
					break;
				}
				else
				{
					tmp = chktyp(i);
					if(tmp != "" && (tmp != *ij))
					{
						i.erase(i.begin());
						i.insert(i.begin(),tmp);
						VAR.erase(it);
						VAR.insert(it,i);
						break;
					}
				}
			}

		}
	}
}



/////////////////////////THE END/////////////////////////////
// final print function

vector<vector<string> > final;
vector<vector<string> > TYPEBCK;
vector<vector<string> > VARBCK;
vector<string> res;
int checkinres(vector<string> t, string s)
{
	vector<string>::iterator it;
	for(it = t.begin(); it!= t.end(); it++)
	{
		if(*it == s)
			return 0;
	}
	return 1;
}

vector<string> makeprin(string t)
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	vector<vector <string> >::iterator ot = TYPE.begin();
	vector <string>::iterator oj;
	vector <string> o;
	int in = 0, jn = 0;
	int flag = 0;
	string type;
	int r = 0;
	res.clear();
	for(it = TYPEBCK.begin();it != TYPEBCK.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && (*ij == t))
			{
				flag = 1;
				type = *ij;
			}
			else if(ij == i.begin() && !(flag == 1))
			{
				ot = TYPE.begin();
				ot = ot + in;
				o = *ot;
				oj = o.begin();
				if(o[0] == t)
				{
					flag = 1;
					type = *ij;
				}
			}
			else if(!(ij == i.begin()) && flag == 1)
			{
				res.push_back(*ij);
			}
		}
		if(!(type == "STRING"||type == "INT"||type == "LONG"||type == "REAL"||type == "BOOLEAN") && !(type.compare(0,7,"UNKNOWN") == 0) && (flag == 1))
		{
			r =checkinres(res, type);
			if(r)
				res.push_back(type);
		}
		flag = 0;
	}
return res;
}
vector<string> makeprin2(string t)
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	vector<vector <string> >::iterator ot = VAR.begin();
	vector <string>::iterator oj;
	vector <string> o;
	int in = 0, jn = 0;
	int flag = 0;
	int r;
	string type = "";
	for(it = VARBCK.begin(); it != VARBCK.end(); it++,in++)
	{
		i = *it;
		for(ij = i.begin(); ij != i.end(); ij++, jn++)
		{
			if(ij == i.begin() && (*ij == t))
			{
				flag = 1;
				type = *ij;
			}
			else if(ij == i.begin() )
			{
				ot = VAR.begin();
				ot = ot + in;
				o = *ot;
				oj = o.begin();
				if(o[0] == t)
				{
					flag = 1;
					type = *ij;
				}
			}
			else if(!(ij == i.begin()) && (flag == 1))
			{
				res.push_back(*ij);
			}
		}
		if(!(type == "STRING"||type == "INT"||type == "LONG"||type == "REAL"||type == "BOOLEAN") && !(type.compare(0,7,"UNKNOWN") == 0) && (flag == 1))
		{
			r = checkinres(res,type);
			if(r)
				res.push_back(type);
		}
		flag = 0;
	}
return res;
}

vector<string> makeprin3(string t)
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;
	vector<vector <string> >::iterator ot;
	vector <string>::iterator oj;
	vector <string> o;
	int in = 0, jn = 0;
	int flag = 0;
	int r;
	string type;
	for(it = prinvec.begin();it != prinvec.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && (*ij == t))
			{
				flag = 1;
				type = *ij;
			}
			else if(ij != i.begin() && flag == 1)
			{
				res.push_back(*ij);
			}
		}
		if(!(type == "STRING"||type == "INT"||type == "LONG"||type == "REAL"||type == "BOOLEAN") && !(type.compare(0,7,"UNKNOWN") == 0) && (flag == 1))
		{
			r = checkinres(res,type);
			if(r)
				res.push_back(type);
		}
		flag = 0;
	}
return res;
}

vector<string> mrg(vector<string> t, vector<string> r)
{
	vector<string>::iterator it;
	for(it = r.begin();it != r.end(); it++)
	{
		t.push_back(*it);
	}
	return t;
}


void prnvt(vector<string> t)
{
	vector<string>::iterator it;
	for(it = t.begin(); it != t.end(); it++)
	{
		cout<<*it<<" ";
	}
}
vector<string> prinnprim;
void Allsysgo()
{
	vector<string> booln;
	vector<string> inte;
	vector<string> lng;
	vector<string> rel;
	vector<string> str;

	vector<string>::iterator it;
	vector<string> h;

	booln.clear();
	booln = makeprin("BOOLEAN");
	booln = makeprin2("BOOLEAN");
	booln = makeprin3("BOOLEAN");
	cout<<"BOOLEAN ";
	prnvt(booln);
	cout<<"#\n";

	inte.clear();
	inte = makeprin("INT");
	inte = makeprin2("INT");
	inte = makeprin3("INT");
	cout<<"INT ";
	prnvt(inte);
	cout<<"#\n";

	lng = makeprin("LONG");
	lng = makeprin2("LONG");
	lng = makeprin3("LONG");
	cout<<"LONG ";
	prnvt(lng);
	cout<<"#\n";

	rel = makeprin("REAL");
	rel = makeprin2("REAL");
	rel = makeprin3("REAL");
	cout<<"REAL ";
	prnvt(rel);
	cout<<"#\n";

	str = makeprin("STRING");
	str = makeprin2("STRING");
	str = makeprin3("STRING");
	cout<<"STRING ";
	prnvt(str);
	cout<<"#\n";

	for(it = prinnprim.begin(); it!= prinnprim.end(); it++)
	{
		h = makeprin(*it);
		h = makeprin2(*it);
		h = makeprin3(*it);
		prnvt(h);
		cout<<"#\n";
	}
}


void ext()
{
	vector<vector <string> >::iterator it;
	vector <string>::iterator ij;
	vector <string> i;

	prinnprim.clear();
	string t;
	int in,jn;
	for(it = TYPE.begin();it != TYPE.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && !(*ij =="STRING" ||*ij =="REAL" ||*ij =="INT" ||*ij =="LONG" ||*ij =="BOOLEAN"))
			{
				if(checkinres(prinnprim,*ij))
					prinnprim.push_back(*ij);
			}

		}
	}
	for(it = VAR.begin();it != VAR.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && !(*ij =="STRING" ||*ij =="REAL" ||*ij =="INT" ||*ij =="LONG" ||*ij =="BOOLEAN"))
			{
				if(checkinres(prinnprim,*ij))
					prinnprim.push_back(*ij);
			}
		}
	}
	for(it = prinvec.begin();it != prinvec.end();it++, in++)
	{
		i = *it;
		for(ij = i.begin();ij != i.end();ij++, jn++)
		{
			if(ij == i.begin() && !(*ij =="STRING" ||*ij =="REAL" ||*ij =="INT" ||*ij =="LONG" ||*ij =="BOOLEAN"))
			{
				if(checkinres(prinnprim,*ij))
					prinnprim.push_back(*ij);
			}
		}
	}
}


// end
//***********&&&&&&&&&&&&&&&&&&&&&((((((((((((((((((((( MAIN )))))))))))))))))))))&&&&&&&&&&&&&&&&&&&****************

int main()
{

    struct programNode* parseTree = program();
    int error_flag = 0;
    parse_tree(parseTree);
    parse_body(parseTree->body);
    string check1 = error_Code_1a();
    if(check1.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 1.1 "<<check1;
    }
    string check2 = error_Code_1b();
    if(check2.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 1.2 "<<check2;
    }
    string check3 = error_Code_1c();
    if(check3.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 1.3 "<<check3;
    }
    string check6 = error_Code_2b();
    if(check6.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 2.2 "<<check6;
   	}
    string check4 = error_Code_1d();
    if(check4.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 1.4 "<<check4;
    }
    string check5 = error_Code_2a();
    if(check5.compare("") != 0 && error_flag == 0)
    {
    	error_flag = 1;
    	cout<<"\nERROR CODE 2.1 "<<check5;
    }
    cout<<"\n";

    if(error_flag == 0)
    {
    	mkmap();
    	mkunkn();
    	typecheck();
    }
    if(errf == 0 && error_flag == 0)
    {
    	mkmap();
    	mkunkn();
    	typecheck();
    	adf1();
		TYPEBCK = TYPE;
		VARBCK = VAR;
		modifytypesec();
		modifyvarsec();
		ext();
		Allsysgo();
    }

    return 0;
}




