//Michael Allen-Bond
//CS355
//Dr. Dang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "symtab.h"
#include "turtle.h"

//EXPLAIN THIS
//SymTab *symtab = NULL;
int lookahead = 0;
LVAL *lval;


//EXPLAIN THIS
enum{
    ASSIGN_STMT = 1, 
    WHILE_STMT, IF_STMT, BLOCK_STMT, ACTION_STMT,
    NUM_EXPR, VAR_EXPR, ADD_EXPR, SUB_EXPR, MULT_EXPR, DIV_EXPR, NEG_EXPR, OR_EXPR, AND_EXPR, NOT_EXPR,
    NE_BOOL, GE_BOOL, LE_BOOL, G_BOOL, L_BOOL, E_BOOL
};


typedef struct Expr {
    int type;  //NUM_EXPR, VAR_EXPR, ADD_EXPR,
    union {
        float num;      //NUM_EXPR
        SymTab *sym;    //VAR_EXPR
        struct Expr *unary;  //unary operation (NEG_EXPR, ... );
        struct {struct Expr *left, *right;} binary;  //binary operation (ADD_EXPR,...);
    } op;
} Expr;

//
typedef struct Stmt {
    int type;  //WHILE_, IF_, ASSIGN_, BLOCK_
    union {
        struct {SymTab *lval; Expr *rval;} assign_;
        struct {Expr *cond; struct Stmt *body;} while_;
        struct {struct Stmt *list;} block_;
        struct {Expr *cond; struct Stmt *body; struct Stmt *elseBody; } if_;
        struct {int action; Expr *rval;} action_;
    } s;
    struct Stmt *next;
} Stmt;

Expr* expr();
Expr* bools();
Stmt* while_stmt();
Stmt* if_stmt();
void executeStmt(Stmt *stmt_);

/**
 *  * Executes an action statement from the turtle API.
 *   */

float evalExpr( Expr *expr )
{
    if (expr==NULL){
        fprintf(stderr , "Syntax Error in Expression Input, exiting.\n");
        
        exit(1);    
    }
    switch(expr->type)
    {
        case NUM_EXPR:
            return expr->op.num;
        case VAR_EXPR:
            return expr->op.sym->val;
        case ADD_EXPR:
            return evalExpr(expr->op.binary.left) + evalExpr(expr->op.binary.right);
        case SUB_EXPR:
            return evalExpr(expr->op.binary.left) - evalExpr(expr->op.binary.right);
        case MULT_EXPR:
            return evalExpr(expr->op.binary.left) * evalExpr(expr->op.binary.right);
        case DIV_EXPR:
            return evalExpr(expr->op.binary.left) / evalExpr(expr->op.binary.right);
        case NEG_EXPR:
            return (-1)*evalExpr(expr->op.unary);
        default:
            return 0;
            break;
    }
}

int evalBool( Expr *expr){
    switch(expr->type)
    {
        case NOT_EXPR:
            if(evalBool(expr->op.unary)==0) return 1;
            else return 0;
        case AND_EXPR:
            if(evalBool(expr->op.binary.left)==0 && (evalBool(expr->op.binary.right))==0) return 0;
            else return 1;
        case OR_EXPR:
            if(evalBool(expr->op.binary.left)==0 || (evalBool(expr->op.binary.right))==0) return 0;
            else return 1;
        case GE_BOOL:
            if(evalExpr(expr->op.binary.left) >= evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        case LE_BOOL:
            if(evalExpr(expr->op.binary.left) <= evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        case NE_BOOL:
            if(evalExpr(expr->op.binary.left) != evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        case G_BOOL:
            if(evalExpr(expr->op.binary.left) > evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        case E_BOOL:
            if(evalExpr(expr->op.binary.left) == evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        case L_BOOL:
            if(evalExpr(expr->op.binary.left) < evalExpr(expr->op.binary.right)) return 0;
            else return 1;
        default:
            return 1;
            break;
       }
}

void execActionStmt(Stmt *stmt)
{
    //printf("excecute action stmt \n");
    int action = stmt->s.action_.action;
    float param;
    switch(action){
        case FORWARD_:
            param = evalExpr(stmt->s.action_.rval);
            //printf("calling turtle forward %f\n", param);

            turtleForward(param);
            break;
        case RIGHT_:
            param = evalExpr(stmt->s.action_.rval);
            
            param = 360-param;
            //printf("%f RIGHT\n", param);
            turtleRotate(param);
            break;
        case LEFT_:
            param=evalExpr(stmt->s.action_.rval);
            //printf("%f LEFT\n",param);
            turtleRotate(param);
            break;
        case HOME_:
            turtleHome();
            break;
        case PENUP_:
            turtlePenUp(1);
            break;
        case PENDOWN_:
            turtlePenUp(0);
            break;
        case PUSHSTATE_:
            turtlePushState();
            break;
        case POPSTATE_:
            turtlePopState();
            break;
        default:
            break;
    }
      

    //execute action statement by calling turtle API
}

void execAssignStmt(Stmt *stmt){
    stmt->s.assign_.lval->val=evalExpr(stmt->s.assign_.rval);
    //printf("%s, %f\n", stmt->s.assign_.lval->sym, stmt->s.assign_.lval->val);
    return;


}
void execBlockStmt(Stmt *stmt){
    Stmt *e;    
    if(stmt->s.block_.list!=NULL)
        e= stmt->s.block_.list;
    while (e!=NULL){
        executeStmt(e);
        e=e->next;
    }
    
}
void execWhileStmt(Stmt *stmt){
    while(evalBool(stmt->s.while_.cond)==0)
        execBlockStmt(stmt->s.while_.body);

}

void execIfStmt(Stmt *stmt){
    Stmt *e;
    if (evalBool(stmt->s.if_.cond)==0)
        execBlockStmt(stmt->s.if_.body);
    else if (stmt->s.if_.elseBody!=NULL){
        e=stmt->s.if_.elseBody;
        if(e->type==IF_STMT)
            executeStmt(e);
        else
            execBlockStmt(e);
    }
    return;
}


void executeStmt(Stmt *stmt_)
{
    //printf("execute stmt %d\n", stmt_->type);

    switch(stmt_->type){
        case ACTION_STMT:
            execActionStmt(stmt_);
            break;
        case ASSIGN_STMT:
            execAssignStmt(stmt_);
            break;
        case WHILE_STMT:
            execWhileStmt(stmt_);
            break;
        case IF_STMT:
            execIfStmt(stmt_);
            break;
        default:
           break; 
    }
    //execute some logics or call turtle API

}
Stmt* createActionStmt(int action, Expr *rval ){


    Stmt *s = (Stmt*) malloc(sizeof(Stmt));
    s->type = ACTION_STMT;
    s->s.action_.action = action;
    s->s.action_.rval = rval;
    return s;
}

Stmt* createAssignStmt(SymTab *lval, Expr *rval){
    Stmt *s = (Stmt*) malloc(sizeof(Stmt));
    s->type = ASSIGN_STMT;
    s->s.assign_.lval=lval;
    s->s.assign_.rval=rval;
    return s;

}

Expr* createBinaryExpr(int type, Expr* e, Expr* f){
    Expr* s=(Expr*) malloc(sizeof(Expr)); 
    s->type=type;
    s->op.binary.left=e;
    s->op.binary.right=f;

    return s;
}


/* enforce match of current token, fetch next token*/
void match(int tok)
{
    if(tok == lookahead)
        lookahead = nextToken(lval);
    else{
        fprintf(stderr,"token matching error: %d\n", tok);
        fprintf(stderr,"Please correct your syntax. Exiting.\n");
        exit(1);
       }

}

Expr* factor(){

    Expr *e;
    switch(lookahead){
        case REAL_:
            e = (Expr*) malloc(sizeof(Expr));
            e->type = NUM_EXPR;
            e->op.num = lval->f;
            lookahead = nextToken(lval);
            return e;
            break;
        case IDENT_:
            e=(Expr*) malloc(sizeof(Expr));
            e->type= VAR_EXPR;
            e->op.sym = symLookup(lval->s);
            lookahead = nextToken(lval);
            return e;
            break;
        case '(':
            match('(');
            e= expr();
            match(')');
            return e;
            break;
        case '-':
            match('-');
            e = (Expr*) malloc(sizeof(Expr));
            e->type = NEG_EXPR;
            e->op.unary=factor();
            return e;
            break;
        case '+':
            match('+');
            e=factor();
            return e;
            break;
        default:
            break;
    }
    return NULL;
}


Expr* term()
{
    Expr *e = factor();
    while(1){
        if(lookahead=='*'){
            match('*');
            e=createBinaryExpr(MULT_EXPR, e, term());
        }
        else if (lookahead=='/'){
            match('/');
            e=createBinaryExpr(DIV_EXPR, e, term());
        }
        else break;
    }
    return e;    
}


Expr*  expr()
{
    Expr *e = term();
    while(1){
        if(lookahead=='+'){
            match('+');
            e=createBinaryExpr(ADD_EXPR, e, term());
        }
        else if (lookahead=='-'){
            match('-');
            e=createBinaryExpr(SUB_EXPR, e, term());
        }
        else break;
    }
    return e;
}

Expr* cmp(){
    Expr *e = expr();
    switch(lookahead){
        case NE_:
            match(NE_);
            e=createBinaryExpr(NE_BOOL, e, expr());
            break;
        case GE_:
            match(GE_);
            e=createBinaryExpr(GE_BOOL, e, expr());
            break;
        case LE_:
            match(LE_);
            e=createBinaryExpr(LE_BOOL, e, expr());
            break;
        case '=':
            match('=');
            e=createBinaryExpr(E_BOOL, e, expr());
            break;
        case '<':
            match('<');
            e=createBinaryExpr(L_BOOL, e, expr());
            break;
        case '>':
            match('>');
            e=createBinaryExpr(G_BOOL, e, expr());
            break;
        default:
            break;
    }
    return e;
    
}

Expr* bool_factor(){
    Expr *e;
    while(1){
        if(lookahead==NOT_){
            match(NOT_);
            e= (Expr*) malloc(sizeof(Expr));
            e->type=NOT_EXPR;
            e->op.unary=bool_factor();
            break;
        }
        else if(lookahead=='('){
            match('(');
            e=bools();
            match(')');
            break;
        }
        else{ 
            e=cmp();
            break;
        }    
    }
    return e;
    
}
Expr* bool_term(){
    Expr *e = bool_factor();
    while(1){
        if(lookahead==AND_){
            match(AND_);
            e=createBinaryExpr(AND_EXPR, e, bool_factor());
        }
        else break;
    }
    return e;
}

Expr* bools(){
    Expr *e = bool_term();
    while (1){
        if(lookahead== OR_){
            match(OR_);
            e=createBinaryExpr(OR_EXPR, e, bool_term());
        }
        else break;
    }
    return e;
}


Stmt* action_stmt()
{

    //printf("action_stmt\n");
    int action = lookahead;
    lookahead = nextToken(lval);

    switch(action){
        case FORWARD_:
            //printf("action_stmt %d %d\n",action, lookahead );
            return createActionStmt(action, expr());
            break;
        case RIGHT_:
            return createActionStmt(action, expr());
            break;
        case LEFT_:
            return createActionStmt(action, expr());
            break;
        case HOME_:
            return createActionStmt(action, NULL);
            break;
        case PENUP_:
            return createActionStmt(action, NULL);
            break;
        case PENDOWN_:
            return createActionStmt(action, NULL);
            break;
        case PUSHSTATE_:
            return createActionStmt(action, NULL);
            break;
        case POPSTATE_:
            return createActionStmt(action, NULL);
            break;                                                
        default:
            break;
    }
    return NULL;
}

Stmt* assign_stmt(){
    Expr *e=expr();

    lookahead=nextToken(lval);
    Expr *r=expr(); 
 
    return createAssignStmt(e->op.sym,r);
}

Stmt* stmt(){
        
    switch(lookahead)
    {
        case FORWARD_:
            //printf("stmt_foward\n");
            return action_stmt();
            break;
        case RIGHT_:
            //printf("stmt_right\n");
            return action_stmt();
            break;
        case LEFT_:
            //printf("stmt_left\n");
            return action_stmt();
            break;
        case HOME_:
            return action_stmt();
            break;
        case PENUP_:
            return action_stmt();
            break;
        case PENDOWN_:
            return action_stmt();
            break;
        case PUSHSTATE_:
            return action_stmt();
            break;
        case POPSTATE_:
            return action_stmt();
            break;
        case IDENT_:
            return assign_stmt();
            break;
        case WHILE_:
            return while_stmt();
            break;
        case IF_:
            return if_stmt();
            break;
        default:
            break;
            	
    }

    return NULL;

}

Stmt* listmake(){
        Stmt* list;
    if (lookahead != OD_ && lookahead != ELSE_ && lookahead != FI_ && lookahead != ELSIF_  && lookahead >=256)
        list=stmt();
    if (list!=NULL)
        if (lookahead != OD_ && lookahead != ELSE_ && lookahead != FI_ && lookahead != ELSIF_  && lookahead >=256)
            list->next=listmake();
    return list;
}

Stmt* getblock(){
    Stmt *block= (Stmt*) malloc(sizeof(Stmt));
    block->type=BLOCK_STMT;
    block->s.block_.list=listmake();
    return block;
}

Stmt* while_stmt(){
    
    match(WHILE_);
    Stmt *stmt=(Stmt*) malloc(sizeof(Stmt));
    stmt->type=WHILE_STMT;
    stmt->s.while_.cond=bools();
    match(DO_);
    stmt->s.while_.body=getblock();
    match(OD_);
    return stmt;
}

Stmt* if_stmt(){
    if (lookahead==IF_)    
        match(IF_);   
    Stmt *ifstmt=(Stmt*) malloc(sizeof(Stmt));
    ifstmt->type=IF_STMT;
    ifstmt->s.if_.cond=bools();
    match(THEN_);
    ifstmt->s.if_.body=getblock();
    if (lookahead==FI_)
        match(FI_);
    if(lookahead==ELSIF_){
        match(ELSIF_);
        ifstmt->s.if_.elseBody=if_stmt();
    }
    if (lookahead==ELSE_){
        match(ELSE_);
        ifstmt->s.if_.elseBody=getblock();
        match(FI_);
    }
    return ifstmt;
        
}


void stmt_seq()
{
    do{
        Stmt *s = stmt(); //Build our AST
        if(s == NULL){
            fprintf(stderr,"execute stmt null, Exiting. \n");
            exit(1);
        }
        executeStmt( s ); //Eval our AST
    }
    while (lookahead != 0 );
}

/* program -> stmt_list */
void program()
{

    //printf("program\n");
    stmt_seq();
}

/* stmt_list -> stmt {stmt}*/
int main(void) {
    lval = (LVAL*) malloc( sizeof(LVAL) );
    turtleInit();
    
    lookahead = nextToken( lval );
    if( !lookahead )
        fprintf(stderr, "Nothing to read\n");
    else
        program();
    
    turtleDumpImage( stdout );
    return 0;

}
