%{
    #include <iostream>
    #include <list>
    #include <fstream>
    #include <string>
    #include <cstdlib>
    using namespace std;

    int global_id = 1;
    const int map_size = 100;
    extern int yylineno;
    extern int yylex();

    void yyerror(char *s) {
        std::cerr << s << ", line " << yylineno << std::endl;
        return;
    }

    struct ParserExpression{
        ParserExpression *expr, *op;
        std::string name;
        bool args, start, finish, main;
        int id;

        ParserExpression(
            std::string name,
            ParserExpression* _expr,
            ParserExpression* op,
            bool main = 0
        ) : id(global_id++), name(name), expr(_expr), op(op), 
            args(0), start(0), finish(0), main(main) {}

        ParserExpression() : id(global_id++), name(""), expr(NULL), op(NULL), 
                             args(0), start(0), finish(0), main(0) {}

        ParserExpression(
            ParserExpression* expr,
            bool args,
            bool start,
            bool finish,
            bool main = 0
        ) : id(global_id++),expr(expr), args(args), 
            start(start), finish(finish), main(main), op(NULL) {}

        ParserExpression(
            ParserExpression* expr,
            bool args,
            bool start,
            bool finish,
            ParserExpression* op
        ) : id(global_id++),expr(expr), args(args), 
            start(start), finish(finish), main(0), op(op) {}

        ParserExpression(ParserExpression* e) {
            if (e == NULL) {
                name = "";
                expr = NULL;
                op = NULL;
                id = global_id++;
            } else {
                name = "";
                expr = e;
                id = global_id++;
                op = NULL;
            }
        }

        void save_to_file(string file_name) {
            ofstream myfile;
            myfile.open (file_name.c_str());
            int root = -save_to_file_helper(myfile);
            myfile << root << endl;
            myfile.close();
        }

        static string to_string(int x) {
            char buffer[33];
            sprintf(buffer, "%d", x);
            return string(buffer);
        }

        int save_to_file_helper(ofstream &file) {
            string expr_string = (expr != NULL) ? to_string(expr->save_to_file_helper(file)) : "0";
            string op_string = (op != NULL) ? to_string(op->save_to_file_helper(file)) : "0";
            string name_string = (name.length()) ? name : "NULL";
            string result = "" + to_string(id) + " " + name_string + " " + to_string((int)args) + " " +
                to_string((int)start) + " " + to_string((int)finish) + " " + to_string((int)main) +
                " " +  expr_string + " " + op_string;

            file << result << endl;

            return id;
        }

        void print(int indent=0) {
            if (args) {
                if (start) std::cout<<"(";
                expr->print(1);
                if (finish) {
                    std::cout<<")";
                } else if (!main) { 
                    std::cout << ", ";
                }
                if (op != NULL) { 
                    if (main && finish) 
                        std::cout << std::endl;
                    op->print();
                }
            } else {
                if (name == "DATASET") {
                    std::cout << name << std::endl;
                    op->print();
                }
                else if (name == "HIDDEN") {
                    if (expr) {
                        expr->print();
                    }
                    if(op != NULL) {
                        op->print();
                    }
                    std::cout << std::endl;
                }
                else {
                    std::cout << name;
                    if(name != "" && !indent) std::cout << " ";
                    if(expr != NULL) expr->print();
                    if(op != NULL && main ) {
                        op->print();
                    }
                }
            }
        }
    };

    struct Root : ParserExpression {
        Root(ParserExpression* str, ParserExpression* o) {
            name = "DATASET";
            expr = str;
            op = o;
            main = true;
        }

        Root(ParserExpression* o) {
            name = "DATASET"; 
            op = o; 
            expr = NULL; 
            main = true; 
        }
    };

    struct List : ParserExpression {
        List(ParserExpression* list, ParserExpression* node) {
            name = "HIDDEN";
            expr = list;
            op = node;
            main = true;
        }
    };

    struct Value : ParserExpression {
        Value(const std::string& text) { name = text;}
    };

    typedef struct {
        std::string str;
        ParserExpression* oper;
        ParserExpression* args;
    } YYSTYPE;

    ParserExpression* tree;

    void read_from_file(ParserExpression* expr, string file_name) {
        ifstream ifs;
        ifs.open (file_name.c_str());
        string s;
        ParserExpression* map[map_size];
        for(int i = 0; i < map_size; i++) {
            map[i] = new ParserExpression();
        }
        int root = 0;
        while(ifs.good()) {
            int id;
            string name;
            int args, finish,start,_main;
            int expr, op;
            ifs >> id;
            if (id < 0) {
                root = -id;
                break;
            }
            ifs >> name >> args >> start >> finish >> _main >> expr >> op;

            map[id]->id = id;
            map[id]->name = (name != "NULL") ? name : "";
            map[id]->args = args;
            map[id]->start = start;
            map[id]->finish = finish;
            map[id]->main = _main;
            map[id]->expr = (expr) ? map[expr] : NULL;
            map[id]->op = (op) ? map[op] : NULL;
        }
        expr = map[root];
    }
%}


//for better debuging
//%error-verbose

%token DD1 DD2 OWFLW BLOCK RECORD SIZE DATASET PUNCHEDCARD RECFRM REL SCAN DEVICE RMNAME FRSPC SEGM MINLEN LOGICAL
%token NUM ID

%type<str> NUM ID DATASET PUNCHEDCARD LOGICAL
%type<oper> OPS TERM ARG LIST_OP OP
%type<expr> DD1 DD2 OWFLW BLOCK RECORD SIZE RECFRM REL SCAN DEVICE RMNAME FRSPC SEGM MINLEN
%type<args> ARGS

%%

PROGRAM: OPS                            { tree = $1; }
;

OPS:    DATASET LIST_OP                     { $$ = new Root($2); }
;


LIST_OP:
LIST_OP','OP { $$ = new List($1, $3); }
| OP { $$ = new List(NULL, $1); }
;


OP: DD1'='TERM			{ $$ = new ParserExpression("DD1", NULL , $3 , true); }
|	DD2'='TERM		{ $$ = new ParserExpression("DD2", $3, NULL, true); }
|	OWFLW'='TERM		{ $$ = new ParserExpression("OWFLW", $3, NULL, true); }
|	BLOCK'='TERM		{ $$ = new ParserExpression("BLOCK", $3, NULL, true); }
|	RECORD'='TERM		{ $$ = new ParserExpression("RECORD", $3, NULL, true); }
|	SIZE'='TERM		{ $$ = new ParserExpression("SIZE", $3, NULL, true); }
|	RECFRM'='TERM		{ $$ = new ParserExpression("RECFRM", $3, NULL, true); }
|	REL'='TERM		{ $$ = new ParserExpression("REL", $3, NULL, true); }
|	SCAN'='TERM		{ $$ = new ParserExpression("SCAN", $3, NULL, true); }
|	DEVICE'='TERM		{ $$ = new ParserExpression("DEVICE", $3, NULL, true); }
|	RMNAME'='TERM		{ $$ = new ParserExpression("RMNAME", $3, NULL, true); }
|	FRSPC'='TERM		{ $$ = new ParserExpression("FRSPC", $3, NULL, true); }
|	SEGM'='TERM		{ $$ = new ParserExpression("SEGM", $3, NULL, true); }
|	MINLEN'='TERM		{ $$ = new ParserExpression("MINLEN", $3, NULL, true); }
|   LOGICAL             { $$ = new ParserExpression("LOGICAL", NULL, NULL, true); }
/* |   LOGICAL             { $$ = "LOGICAL"; } */
;

TERM:   NUM                             { $$ = new Value($1); }
|       ID                              { $$ = new Value($1); }
|       '('ARGS')'                 	{ $$ = new ParserExpression($2, true, true, false, true); }
;

ARGS:                                   { }
|       ARG                             { $$ = new ParserExpression($1, true, false, true); }
|       ARG ',' ARGS                    { $$ = new ParserExpression($1, true, false, false, $3); }
//one more
;

ARG:	NUM				{ $$ = new Value($1); }
|	ID				{ $$ = new Value($1); }
;
%%

int main() { 
    yyparse();
    if (tree == NULL) { 
        return 0;
    }
    tree->save_to_file("example.txt");
    read_from_file(tree, "example.txt");
    std::cout << "PRINTING PARSED COMMAND:\n======================\n\n";
    tree->print(0);
    std::cout << '\n';
    return 0; 
}
