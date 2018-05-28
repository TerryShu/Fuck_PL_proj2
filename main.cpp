# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <ctype.h>
# include <iomanip>


using namespace std;

// ======================Data Struct==============================
enum Error_type{ UNRECOGNIZED, UNDEFINED, UNEXPECTED, ERROR, QUIT };

struct Def_Data{
  string Def_Name ;
  string Def_type ;
  bool isArray ;
  string array_size ;
} ;

struct Temp_Def_Data{
  string Def_Name ;
  string Def_type ;
  bool isArray ;
  string array_size ;
  bool defed ;
} ;

struct Function_Def_Data{
  string Def_Name ;
  string Def_type ;
  vector<string> Function_info ;
} ;

struct Temp_Function_Def_Data{
  string Def_Name ;
  string Def_type ;
  vector<string> Function_info ;
  bool defed ;
} ;

// ===============================================================

// ======================global var===============================
string gNowToken ;
string gBoolAns ;
vector<Def_Data> gDef ;
int gTestNum = 0 ;
bool gChange = false ;
bool gIsBoolOP = false ;
bool gQuit = false ;
bool gIsFloat = false ;
char gUnknowChar ;
int gLines = 0 ;
string gDoFunctionName ;
bool gSystemFunction = false ;
string gDef_name_or_function ;
string gDef_var_type ;
bool gDefed = false ;
bool gIn_From_Def = false ;
vector<Temp_Def_Data> gTemp_def ;
vector<string> gStore_function_info ;
bool gIs_function_Def = false ;
// ===============================================================

// =======================Initialize==============================
void InitializeState() ;
// ===============================================================

// =======================use for get token=======================
string GetToken() ;
void SkipExitChar() ;
string ReadConstant() ;
string ReadIdent() ;
string ReadOPAndComment() ;
void TakeToken() ;
void ReadAfterError() ;
// ===============================================================

// =======================Judge Token=============================
bool JudgeTypeSpec( string token ) ;
bool JudgeIDENT( string Token ) ;
bool JudgeNum( string Token ) ;
bool JudgeFloat( string Token ) ;
bool JudgeInt( string Token ) ;
bool JudgeConstant( string Token ) ;
// ===============================================================

// =======================Recursive===============================
void User_input() ;
void Definition() ;
void Statement() ;
void Function_definition_without_ID() ;
void Function_definition_or_declarators() ;
void Formal_parameter_list() ;
void Compound_statement() ;
void Rest_of_declarators() ;
void Basic_expression() ;
void Expression() ;
void Rest_of_Identifier_started_basic_exp() ;
void Rest_of_PPMM_Identifier_started_basic_exp() ;
void Signed_unary_exp() ;
void Romce_and_romloe() ;
void Actual_parameter_list() ;
void Rest_of_maybe_logical_OR_exp() ;
void Rest_of_maybe_logical_AND_exp() ;
void Maybe_logical_AND_exp() ;
void Rest_of_maybe_bit_OR_exp() ;
void Maybe_bit_OR_exp() ;
void Rest_of_maybe_bit_ex_OR_exp() ;
void Maybe_bit_ex_OR_exp() ;
void Maybe_bit_AND_exp() ;
void Rest_of_maybe_bit_ex_OR_exp() ;
void Maybe_bit_AND_exp() ;
void Maybe_equality_exp() ;
void Maybe_relational_exp() ;
void Maybe_shift_exp() ;
void Maybe_additive_exp() ;
void Rest_of_maybe_additive_exp() ;
void Rest_of_maybe_shift_exp() ;
void Maybe_mult_exp() ;
void Rest_of_maybe_mult_exp() ;
void Rest_of_maybe_bit_AND_exp() ;
void Rest_of_maybe_equality_exp() ;
void Rest_of_maybe_relational_exp() ;
void Unary_exp() ;
void DoSystemFunction() ;
void DefInitStage()  ;
void DefOutput() ;
// ===============================================================


int main() {
  /*int testNum ;
  cin >> testNum ;*/

  while ( !gQuit ) {
    InitializeState() ;
    try {
      cout << "Our-C running ..." << endl ;
      User_input() ;
    } // try
    catch ( Error_type error ) {
      ReadAfterError() ;
      if ( error == UNRECOGNIZED ) {
        cout << "Unrecognized token with first char : '" << gUnknowChar << "'" << endl ;
      } // if
      else if ( error == UNDEFINED ) {
        cout << "Undefined identifier : '" << gNowToken << "'" << endl ;
      } // else if
      else if ( error == UNEXPECTED ) {
        cout << "Unexpected token : '" << gNowToken << "'" << endl ;
      } // else if
      else if ( error == ERROR ) {
        cout << "Error" << endl ;
        return 0 ;
      } // else if
      else if ( error == QUIT ) {
        cout << "> Our-C exited ..." ;
      } // else if
    } // catch
  } // while

} // main()

string GetToken() {

  if ( !gNowToken.empty() ) {
    return gNowToken ;
  } // if

  char aChar ;
  char peekChar ;
  SkipExitChar() ; // skip white space and other
  string token = "" ;
  peekChar = cin.peek() ;
  if ( isalnum( peekChar ) || peekChar == '_' || peekChar == '.'
       || peekChar == '\'' || peekChar == '"' ) {
    if ( isdigit( peekChar ) || peekChar == '.' || peekChar == '\'' || peekChar == '"' ) {
      token = ReadConstant() ;
    } // if
    else {
      token = ReadIdent() ;
    } // else

  } // if
  else if ( peekChar == '(' || peekChar == ')' || peekChar == '[' || peekChar == ']' ||
            peekChar == '{' || peekChar == '}' || peekChar == '+' || peekChar == '-' ||
            peekChar == '*' || peekChar == '/' || peekChar == '%' || peekChar == '^' ||
            peekChar == '>' || peekChar == '<' || peekChar == '!' || peekChar == '&' ||
            peekChar == '|' || peekChar == '=' || peekChar == ';' || peekChar == ',' ||
            peekChar == '?' || peekChar == ':' ) {
    token = ReadOPAndComment() ;
  } // else if
  else {
    if ( !isalnum( peekChar ) && peekChar != '_' && peekChar != '(' && peekChar != ')' &&
         peekChar != '{' && peekChar != '}' && peekChar != '+' && peekChar != '-' &&
         peekChar != '*' && peekChar != '/' && peekChar != '%' && peekChar != '^' &&
         peekChar != '>' && peekChar != '<' && peekChar != '!' && peekChar != '&' &&
         peekChar != '|' && peekChar != '=' && peekChar != ';' && peekChar != ',' &&
         peekChar != '?' && peekChar != ':' && peekChar != '[' && peekChar != ']' ) {
      gUnknowChar = peekChar ;
      throw UNRECOGNIZED ;
    } // if all possibly start

  } // else



  return token ;

} // GetToken()

string ReadConstant() {
  char aChar ;
  char peekChar ;
  string token ;
  token.clear() ;

  peekChar = cin.peek() ;

  if ( peekChar == '.' ) {
    aChar = cin.get() ; // read '.'
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( isdigit( peekChar ) ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while
  } // if
  else if ( isdigit( peekChar ) ) {
    while ( isdigit( peekChar ) ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    if ( peekChar == '.' ) {
      aChar = cin.get() ; // read '.'
      token = token + aChar ;
      peekChar = cin.peek() ;
      while ( isdigit( peekChar ) ) {
        aChar = cin.get() ;
        token = token + aChar ;
        peekChar = cin.peek() ;
      } // while
    } // if

  } // else if
  else if ( peekChar == '\'' ) {
    aChar = cin.get() ; // read '
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( peekChar != '\'' ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    aChar = cin.get() ; // read '
    token = token + aChar ;
  }  // else if
  else if ( peekChar == '"' ) {
    aChar = cin.get() ; // read "
    token = token + aChar ;
    peekChar = cin.peek() ;
    while ( peekChar != '"' ) {
      aChar = cin.get() ;
      token = token + aChar ;
      peekChar = cin.peek() ;
    } // while

    aChar = cin.get() ; // read '
    token = token + aChar ;
  }  // else if

  return token ;
} // ReadConstant()

string ReadIdent() {
  char aChar ;
  char peekChar ;
  string token ;
  token.clear() ;

  peekChar = cin.peek() ;
  while ( isalnum( peekChar ) || peekChar == '_' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
  } // while

  return token ;
} // ReadIdent()

string ReadOPAndComment() {
  char peekChar ;
  char aChar ;
  string token ;
  token.clear() ;
  peekChar = cin.peek() ;

  if ( peekChar == '(' || peekChar == ')' || peekChar == '[' || peekChar == ']' ||
       peekChar == '{' || peekChar == '}' || peekChar == ';' || peekChar == ',' ||
       peekChar == '?' || peekChar == ':' ) {
    aChar = cin.get() ;
    token = token + aChar ;
  } // if
  else if ( peekChar == '+' || peekChar == '-' || peekChar == '*' ||
            peekChar == '/' || peekChar == '%' || peekChar == '^' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( aChar == '+' || aChar == '-' ) {

      if ( peekChar == '=' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // if += -+
      else if ( aChar == '+' && peekChar == '+' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // else if ++
      else if ( aChar == '-' && peekChar == '-' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // else if --

    } // if
    else if ( aChar == '*' || aChar == '/' || aChar == '%' || aChar == '^' ) {

      if ( peekChar == '=' ) {
        aChar = cin.get() ;
        token = token + aChar ;
      } // if
      else if ( aChar == '/' && peekChar == '/' ) {
        char comment[500] ;
        cin.getline( comment, 500 ) ;
        token = GetToken() ;
      } // else if comment

    } // else if
  } // else if
  else if ( peekChar == '>' || peekChar == '<' || peekChar == '=' || peekChar == '!' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( peekChar == '=' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // if >= <= ==
    else if ( aChar == '>' && peekChar == '>' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if >>
    else if ( aChar == '<' && peekChar == '<' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if <<

  } // else if
  else if ( peekChar == '&' || peekChar == '|' ) {
    aChar = cin.get() ;
    token = token + aChar ;
    peekChar = cin.peek() ;
    if ( aChar == '&' && peekChar == '&' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // if
    else if ( aChar == '|' && peekChar == '|' ) {
      aChar = cin.get() ;
      token = token + aChar ;
    } // else if

  } // else if

  return token ;
} // ReadOPAndComment()

void ReadAfterError() {
  char aChar ;
  aChar = cin.peek() ;
  while ( aChar != '\n' ) {
    aChar = cin.get() ;
    aChar = cin.peek() ;
  } // while
} // ReadAfterError()

void InitializeToken() {
  gNowToken.clear() ;
} // InitializeToken()

void InitializeState() {
  gNowToken.clear() ;
  gBoolAns.clear() ;
  gIsFloat = false ;
  gQuit = false ;
  gIsBoolOP = false ;
  gChange = false ;
  gUnknowChar = '\0' ;
} // InitializeState()

void TakeToken() {
  if ( gIs_function_Def ) {
    gStore_function_info.push_back( gNowToken ) ;
  } // if
  gNowToken.clear() ;
} // TakeToken()

void SkipExitChar() {
  char aChar ;
  char exitChar ;
  aChar = cin.peek() ;

  if ( aChar != ' ' && aChar != '\n' && aChar != '\0' && aChar != '\t' ) {
    return ;
  } // if
  else {

    while ( aChar == ' ' || aChar == '\n' || aChar == '\0' || aChar == '\t' ) {
      exitChar = cin.get() ;
      aChar = cin.peek() ;
      if ( aChar == '\n' ) {
        gLines++ ;
      } // if
    } // while

  } // else

} // SkipExitChar()

bool JudgeIDENT( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;

  if ( Token == "int" || Token == "float" || Token == "char" ||
       Token == "bool" || Token == "string" || Token == "void" ||
       Token == "if" || Token == "else" || Token == "while" ||
       Token == "do" || Token == "return" || Token == "true" || Token == "false" ) {
    return false ;
  } // if

  if ( isalpha( Token.at( 0 ) ) || Token.at( 0 ) == '_' ) {
    correct++ ;
  } // if a~z||A~Z|| _

  for ( int i = 1 ; i < length ; i++ ) {
    if ( isalnum( Token.at( i ) ) || Token.at( i ) == '_' ) {
      correct++ ;
    } // if  a~z || A~Z || 0~9 || _
  } // for

  if ( correct == length ) return true ;

  return false ;

} // JudgeIDENT()

bool JudgeNum( string Token ) {
  if ( JudgeFloat( Token ) || JudgeInt( Token ) ) {
    return true ;
  } // if

  return false ;
} // JudgeNum()

bool JudgeInt( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;
  for ( int i = 0 ; i < length ; i++ ) {
    if ( Token.at( i ) >= '0' && Token.at( i ) <= '9' ) {
      correct++ ;
    } // if  0~9
  } // for

  if ( correct == length ) return true ;

  return false ;
} // JudgeInt()

bool JudgeFloat( string Token ) {
  int length = Token.length() ;
  int correct = 0 ;
  bool find_point = false ;

  if ( Token == "." ) {
    return false ;
  } // if just one point '.'

  for ( int i = 0 ; i < length ; i++ ) {
    if ( Token.at( i ) >= '0' && Token.at( i ) <= '9' ) {
      correct++ ;
    } // if  0~9
    else if ( Token.at( i ) == '.' && !find_point ) {
      correct++ ;
      find_point = true ;
    } // else if judge 123.111 && .2 && 2. should take care
  } // for

  if ( correct == length && find_point ) return true ;

  return false ;
} // JudgeFloat()

bool JudgeTypeSpec( string Token ) {

  if ( Token == "int" || Token == "float" || Token == "char" ||
       Token == "bool" || Token == "string" ) {
    return true ;
  } // if

  return false ;
} // JudgeTypeSpec()

bool JudgeConstant( string Token ) {
  char first_char = Token[0] ;
  char last_char = Token[ ( Token.length() - 1 ) ] ;

  if ( JudgeNum( Token ) ) {
    return true ;
  } // if
  else if ( ( first_char == '\'' && last_char == '\'' ) || ( first_char == '"' && last_char == '"' ) ) {
    return true ;
  } // else if 'aaa' "aaa"
  else if ( Token == "true" || Token == "false" ) {
    return true ;
  } // else if
  else {
    return false ;
  } // else

  return false ;

} // JudgeConstant()

bool JudgeStatment( string Token ) {
  if ( Token == ";" || Token == "return" || Token == "if" || Token == "while" ||
       Token == "do" || Token == "{" || Token == "++" || Token == "--" ||
       JudgeIDENT( Token ) || Token == "+" || Token == "-" || Token == "!" ||
       JudgeConstant( Token ) ) {
    return true ;
  } // if

  return false ;

} // JudgeStatment()

void User_input() {
  gNowToken = GetToken() ;

  if ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) ) {
    gIn_From_Def = true ;
    Definition() ;
    DefOutput() ;
    DefInitStage() ;
    gIn_From_Def = false ;
  } // if
  else if ( JudgeStatment( gNowToken ) ) {
    Statement() ;
    cout << "> Statement executed ..." << endl ;
  } // else if
  else {
    throw UNEXPECTED ;
  } // else

  gNowToken = GetToken() ;
  while ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) || JudgeStatment( gNowToken ) ) {
    if ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) ) {
      gIn_From_Def = true ;
      Definition() ;
      DefOutput() ;
      DefInitStage() ;
      gIn_From_Def = false ;
    } // if
    else if ( JudgeStatment( gNowToken ) ) {
      Statement() ;
      cout << "> Statement executed ..." << endl ;
    } // else if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
  } // while
} // User_input()

void DefInitStage() {
  gDefed = false ;
  gDef_name_or_function.clear() ;
} // DefInitStage()

void Definition() {
  gNowToken = GetToken() ;
  if ( gNowToken == "void" ) {
    gDef_var_type = gNowToken ;
    TakeToken() ; // take void
    gNowToken = GetToken() ; // get IDENT
    if ( JudgeIDENT( gNowToken ) ) {
      gDef_name_or_function = gNowToken ;
      TakeToken() ;
      Function_definition_without_ID() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // if
  else if ( JudgeTypeSpec( gNowToken ) ) {
    TakeToken() ; // take type_spec
    gNowToken = GetToken() ; // get IDENT

    if ( JudgeIDENT( gNowToken ) ) {
      gDef_name_or_function = gNowToken ;
      TakeToken() ;
      Function_definition_or_declarators() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // else if
  else {
    throw UNEXPECTED ;
  } // else

} // Definition()

void DefOutput() {
  if ( !gDefed ) {
    cout << "> Definition of " << gDef_name_or_function << " entered ..." << endl ;
  } // if
  else {
    cout << "> New definition of " << gDef_name_or_function << " entered ..." << endl ;
  } // else
} // DefOutput()

void Statement() {
  gNowToken = GetToken() ;
  if ( gNowToken == ";" ) {
    TakeToken() ;
  } // if null statement
  else if ( gNowToken == "return" ) {
    TakeToken() ; // take return
    gNowToken = GetToken() ;
    if ( JudgeIDENT( gNowToken ) || gNowToken == "++" || gNowToken == "--" ||
         gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ||
         gNowToken == "(" || JudgeConstant( gNowToken ) ) {
      Expression() ;
    } // if

    gNowToken = GetToken() ;
    if ( gNowToken == ";" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // else if
  else if ( gNowToken == "if" ) {
    TakeToken() ; // take if
    gNowToken = GetToken() ;
    if ( gNowToken == "(" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    Statement() ;
    gNowToken = GetToken() ;
    if ( gNowToken == "else" ) {
      TakeToken() ;
      gNowToken = GetToken() ;
      Statement() ;
    }  // if

  } // else if
  else if ( gNowToken == "while" ) {
    TakeToken() ; // take while
    gNowToken = GetToken() ;
    if ( gNowToken == "(" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    Statement() ;
  } // else if
  else if ( gNowToken == "do" ) {
    TakeToken() ; // take do
    gNowToken = GetToken() ;
    Statement() ;
    gNowToken = GetToken() ;
    if ( gNowToken == "while" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    if ( gNowToken == "(" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    if ( gNowToken == ";" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // else if
  else if ( gNowToken == "{" ) {
    Compound_statement() ;
  } // else if
  else {
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ";" ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else
  } // else

} // Statement()

void Function_definition_without_ID() {
  gNowToken = GetToken() ; // get IDENT

  if ( gNowToken == "(" ) {
    gIs_function_Def = true ;
    TakeToken() ; // take "("
    gNowToken = GetToken() ; // get  [ VOID | formal_parameter_list ]


    if ( gNowToken == "void" ) {
      TakeToken() ; // take void
    } // if VOID
    else if ( JudgeTypeSpec( gNowToken ) ) {
      Formal_parameter_list() ;
    } // else if formal_parameter_list


    gNowToken = GetToken() ; // get  ")"


    if ( gNowToken == ")" ) {
      TakeToken() ; // take ")"
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // if  '(' [ VOID | formal_parameter_list ] ')' compound_statement
  else {
    throw UNEXPECTED ;
  } // else

  Compound_statement() ;
  gIs_function_Def = false ;

} // Function_definition_without_ID()

void Function_definition_or_declarators() {
  gNowToken = GetToken() ;
  if ( gNowToken == "(" ) {
    Function_definition_without_ID() ;
  } // if function_definition_without_ID
  else {
    Rest_of_declarators() ;
  } // else

} // Function_definition_or_declarators()

void Expression() {
  gNowToken = GetToken() ;
  Basic_expression() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "," ) {
    TakeToken() ;
    Basic_expression() ;
    gNowToken = GetToken() ;
  } // while
} // Expression()

void Basic_expression() {
  gNowToken = GetToken() ;
  if ( JudgeIDENT( gNowToken ) ) {
    gDoFunctionName = gNowToken ;
    if ( gDoFunctionName == "ListAllVariables" ||
         gDoFunctionName == "ListAllFunctions" ||
         gDoFunctionName == "ListVariable" ||
         gDoFunctionName == "ListFunction" ||
         gDoFunctionName == "Done" ) {
      gSystemFunction = true ;
    } // if

    TakeToken() ; // take ID
    Rest_of_Identifier_started_basic_exp() ;
  } // if Identifier rest_of_Identifier_started_basic_exp
  else if ( gNowToken == "++" || gNowToken == "--" ) {
    TakeToken() ; // take ++ or --
    gNowToken = GetToken() ; // get IDENT
    if ( JudgeIDENT( gNowToken ) ) {
      TakeToken() ; // take IDENT
      Rest_of_PPMM_Identifier_started_basic_exp() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else
  } // else if ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
  else if ( gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ) {
    TakeToken() ; // take + or - or !
    gNowToken = GetToken() ;
    while ( gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ) {
      if ( gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ) {
        TakeToken() ; // take + or - or !
      } // if

      gNowToken = GetToken() ;
    } // while

    Signed_unary_exp() ;
    Romce_and_romloe() ;
  } // else if sign { sign } signed_unary_exp romce_and_romloe
  else if ( JudgeConstant( gNowToken ) || gNowToken == "(" ) {
    if ( JudgeConstant( gNowToken ) ) {
      TakeToken() ;
    } // if
    else if ( gNowToken == "(" ) {
      TakeToken() ;
      gNowToken = GetToken() ;
      Expression() ;
      gNowToken = GetToken() ;
      if ( gNowToken == ")" ) {
        TakeToken() ;
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // else if
    else {
      throw UNEXPECTED ;
    } // else

    Romce_and_romloe() ;
  } // else if ( Constant | '(' expression ')' ) romce_and_romloe
  else {
    throw UNEXPECTED ;
  } // else
} // Basic_expression()

void Rest_of_Identifier_started_basic_exp() {
  gNowToken = GetToken() ;
  if ( gNowToken == "(" ) {
    TakeToken() ; // take (
    if ( gSystemFunction ) {
      DoSystemFunction() ;
    } // if

    gNowToken = GetToken() ;
    if ( JudgeIDENT( gNowToken ) || gNowToken == "++" || gNowToken == "--" || gNowToken == "+" ||
         gNowToken == "-" || gNowToken == "!" || JudgeConstant( gNowToken ) || gNowToken == "(" ) {
      Actual_parameter_list() ;
    } // if

    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ; // take )
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    Romce_and_romloe() ;

  } // if
  else {

    gNowToken = GetToken() ;
    if ( gNowToken == "[" ) {
      TakeToken() ;
      gNowToken = GetToken() ;
      Expression() ;
      gNowToken = GetToken() ;
      if ( gNowToken == "]" ) {
        TakeToken() ;
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // if

    gNowToken = GetToken() ;
    if ( gNowToken == "=" || gNowToken == "+=" || gNowToken == "-=" ||
         gNowToken == "*=" || gNowToken == "/=" || gNowToken == "%=" ) {
      TakeToken() ;
      Basic_expression() ;
    } // if
    else if ( gNowToken == "++" || gNowToken == "--" ) {
      TakeToken() ;
      Romce_and_romloe() ;
    } // else if
    else {
      Romce_and_romloe() ;
    } // else
  } // else

} // Rest_of_Identifier_started_basic_exp()

void DoSystemFunction() {
  if ( gDoFunctionName == "Done" ) {
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ;
    } // if

    gNowToken = GetToken() ;
    if ( gNowToken == ";" ) {
      gQuit = true ;
      throw QUIT ;
    } // if
  } // if
} // DoSystemFunction()

void Rest_of_PPMM_Identifier_started_basic_exp() {
  gNowToken = GetToken() ;
  if ( gNowToken == "[" ) {
    TakeToken() ; // take [
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == "]" ) {
      TakeToken() ; // take ]
    } // if
  } // if

  gNowToken = GetToken() ;
  Romce_and_romloe() ;
} // Rest_of_PPMM_Identifier_started_basic_exp()

void Signed_unary_exp() {
  gNowToken = GetToken() ;
  if ( JudgeIDENT( gNowToken ) ) {
    TakeToken() ; // take IDENT
    gNowToken = GetToken() ;
    if ( gNowToken == "(" ) {
      TakeToken() ; // take (
      gNowToken = GetToken() ;
      if ( JudgeIDENT( gNowToken ) || gNowToken == "++" || gNowToken == "--" ||
           gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ||
           JudgeConstant( gNowToken ) || gNowToken == "(" ) {
        Actual_parameter_list() ;
      } // if

      gNowToken = GetToken() ;
      if ( gNowToken == ")" ) {
        TakeToken() ; // take )
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // if
    else if ( gNowToken == "[" ) {
      TakeToken() ; // take "["
      Expression() ;
      gNowToken = GetToken() ;
      if ( gNowToken == "]" ) {
        TakeToken() ; // take ]
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // else if

  } // if Identifier [ '(' [ actual_parameter_list ] ')' |'[' expression ']' ]
  else if ( JudgeConstant( gNowToken ) ) {
    TakeToken() ; // take Constant
  } // else if Constant
  else if ( gNowToken == "(" ) {
    TakeToken() ; // take (
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ; // take )
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // else if '(' expression ')'

} // Signed_unary_exp()

void Unsigned_unary_exp() {
  gNowToken = GetToken() ;
  if ( JudgeIDENT( gNowToken ) ) {
    TakeToken() ; // take IDENT
    gNowToken = GetToken() ;
    if ( gNowToken == "(" ) {
      TakeToken() ; // take (
      gNowToken = GetToken() ;
      if ( JudgeIDENT( gNowToken ) || gNowToken == "++" || gNowToken == "--" ||
           gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ||
           JudgeConstant( gNowToken ) || gNowToken == "(" ) {
        Actual_parameter_list() ;
      } // if

      gNowToken = GetToken() ;
      if ( gNowToken == ")" ) {
        TakeToken() ; // take )
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // if
    else if ( gNowToken == "[" ) {
      TakeToken() ; // take "["
      Expression() ;
      gNowToken = GetToken() ;
      if ( gNowToken == "]" ) {
        TakeToken() ; // take ]
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // else if

    gNowToken = GetToken() ;
    if ( gNowToken == "++" || gNowToken == "--" ) {
      TakeToken() ; // take ++ or --
    } // if
  } // if Identifier [ '(' [ actual_parameter_list ] ')' |'[' expression ']' ] [ ( PP | MM ) ] ]
  else if ( JudgeConstant( gNowToken ) ) {
    TakeToken() ; // take Constant
  } // else if Constant
  else if ( gNowToken == "(" ) {
    TakeToken() ; // take (
    Expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ")" ) {
      TakeToken() ; // take )
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // else if '(' expression ')'
} // Unsigned_unary_exp()

void Romce_and_romloe() {
  gNowToken = GetToken() ;
  Rest_of_maybe_logical_OR_exp() ;
  gNowToken = GetToken() ;
  if ( gNowToken == "?" ) {
    TakeToken() ; // take ?
    Basic_expression() ;
    gNowToken = GetToken() ;
    if ( gNowToken == ":" ) {
      TakeToken() ; // take :
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    Basic_expression() ;
  } // if

} // Romce_and_romloe()

void Rest_of_maybe_logical_OR_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_logical_AND_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "||" ) {
    TakeToken() ; // take ||
    Maybe_logical_AND_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_logical_OR_exp()

void Rest_of_maybe_logical_AND_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_bit_OR_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "&&" ) {
    TakeToken() ; // take &&
    Maybe_bit_OR_exp() ;
    gNowToken = GetToken() ;
  } // while { AND maybe_bit_OR_exp }
} // Rest_of_maybe_logical_AND_exp()

void Rest_of_maybe_bit_OR_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_bit_ex_OR_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "|" ) {
    TakeToken() ; // take |
    Maybe_bit_ex_OR_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_bit_OR_exp()

void Maybe_logical_AND_exp() {
  gNowToken = GetToken() ;
  Maybe_bit_OR_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "&&" ) {
    TakeToken() ; // take &&
    Maybe_bit_OR_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_logical_AND_exp()

void Maybe_bit_OR_exp() {
  gNowToken = GetToken() ;
  Maybe_bit_ex_OR_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "|" ) {
    TakeToken() ; // take |
    Maybe_bit_ex_OR_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_bit_OR_exp()

void Maybe_bit_ex_OR_exp() {
  gNowToken = GetToken() ;
  Maybe_bit_AND_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "^" ) {
    TakeToken() ; // take ^
    Maybe_bit_AND_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_bit_ex_OR_exp()

void Rest_of_maybe_bit_ex_OR_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_bit_AND_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "^" ) {
    TakeToken() ; // take ^
    Maybe_bit_AND_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_bit_ex_OR_exp()

void Rest_of_maybe_bit_AND_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_equality_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "&" ) {
    TakeToken() ; // take &
    Maybe_equality_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_bit_AND_exp()

void Maybe_bit_AND_exp() {
  gNowToken = GetToken() ;
  Maybe_equality_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "&" ) {
    TakeToken() ; // take &
    Maybe_equality_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_bit_AND_exp()

void Maybe_equality_exp() {
  gNowToken = GetToken() ;
  Maybe_relational_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "==" || gNowToken == "!=" ) {
    TakeToken() ; // take == !=
    Maybe_relational_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_equality_exp()

void Rest_of_maybe_equality_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_relational_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "==" || gNowToken == "!=" ) {
    TakeToken() ; // take == !=
    Maybe_relational_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_equality_exp()

void Maybe_relational_exp() {
  gNowToken = GetToken() ;
  Maybe_shift_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "<" || gNowToken == ">" || gNowToken == ">=" || gNowToken == ">=" ) {
    TakeToken() ;
    Maybe_shift_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_relational_exp()

void Maybe_shift_exp() {
  gNowToken = GetToken() ;
  Maybe_additive_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "<<" || gNowToken == ">>" ) {
    TakeToken() ;
    Maybe_additive_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_shift_exp()

void Maybe_additive_exp() {
  gNowToken = GetToken() ;
  Maybe_mult_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "+" || gNowToken == "-" ) {
    TakeToken() ;
    Maybe_mult_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Maybe_additive_exp()

void Rest_of_maybe_shift_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_additive_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "<<" || gNowToken == ">>" ) {
    TakeToken() ;
    Maybe_additive_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_shift_exp()

void Rest_of_maybe_additive_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_mult_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "+" || gNowToken == "-" ) {
    TakeToken() ;
    Maybe_mult_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_additive_exp()

void Maybe_mult_exp() {
  gNowToken = GetToken() ;
  Unary_exp() ;
  gNowToken = GetToken() ;
  Rest_of_maybe_mult_exp() ;
} // Maybe_mult_exp()

void Unary_exp() {
  gNowToken = GetToken() ;
  if ( gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ) {
    TakeToken() ;
    gNowToken = GetToken() ;
    while ( gNowToken == "+" || gNowToken == "-" || gNowToken == "!" ) {
      TakeToken() ;
    } // while

    gNowToken = GetToken() ;
    Signed_unary_exp() ;
  } // if
  else if ( gNowToken == "++" || gNowToken == "--" ) {
    TakeToken() ; // take ++ --
    gNowToken = GetToken() ;
    if ( JudgeIDENT( gNowToken ) ) {
      TakeToken() ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
    if ( gNowToken == "[" ) {
      TakeToken() ;
      gNowToken = GetToken() ;
      Expression() ;
      gNowToken = GetToken() ;
      if ( gNowToken == "]" ) {
        TakeToken() ;
      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // if
  } // else if
  else {
    Unsigned_unary_exp() ;
  } // else

} // Unary_exp()

void Rest_of_maybe_mult_exp() {
  gNowToken = GetToken() ;
  while ( gNowToken == "*" || gNowToken == "/" || gNowToken == "%" ) {
    TakeToken() ;
    Unary_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_mult_exp()

void Rest_of_maybe_relational_exp() {
  gNowToken = GetToken() ;
  Rest_of_maybe_shift_exp() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "<" || gNowToken == ">" || gNowToken == ">=" || gNowToken == ">=" ) {
    TakeToken() ;
    Maybe_shift_exp() ;
    gNowToken = GetToken() ;
  } // while
} // Rest_of_maybe_relational_exp()

void Actual_parameter_list() {
  Basic_expression() ;
  gNowToken = GetToken() ;
  while ( gNowToken == "," ) {
    TakeToken() ; // take ","
    Basic_expression() ;
    gNowToken = GetToken() ;
  } // while
} // Actual_parameter_list()

void Formal_parameter_list() {
  gNowToken = GetToken() ; // get type_specifier
  if ( JudgeTypeSpec( gNowToken ) ) {
    TakeToken() ;

    gNowToken = GetToken() ; // get [ '&' ] or Identifier

    if ( gNowToken == "&" ) {
      TakeToken() ; // take "&"
    } // if

    gNowToken = GetToken() ; // get [ '&' ] or Identifier

    if ( JudgeIDENT( gNowToken ) ) {
      TakeToken() ; // take IDENT
    } // if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ; // get [ '&' ] or Identifier


    if ( gNowToken == "[" ) {
      TakeToken() ;

      gNowToken = GetToken() ; // get constant

      if ( JudgeConstant( gNowToken ) ) {
        TakeToken() ;

        gNowToken = GetToken() ; // get constant

        if ( gNowToken == "[" ) {
          TakeToken() ;
          gNowToken = GetToken() ; // get constant
          if ( JudgeConstant( gNowToken ) ) {
            TakeToken() ;
          } // if
          else {
            throw UNEXPECTED ;
          } // else

          gNowToken = GetToken() ; // get "]"
          if ( gNowToken == "]" ) {
            TakeToken() ;
          } // if
          else {
            throw UNEXPECTED ;
          } // else

        } // if

        gNowToken = GetToken() ; // get constant

        if ( gNowToken == "," ) {
          while ( gNowToken == "," ) {
            TakeToken() ;
            gNowToken = GetToken() ; // get type
            if ( JudgeTypeSpec( gNowToken ) ) {
              TakeToken() ;
            } // if
            else {
              throw UNEXPECTED ;
            } // else

            gNowToken = GetToken() ; // get constant

            if ( gNowToken == "&" ) {
              TakeToken() ;
            } // if


            gNowToken = GetToken() ; // get constant

            if ( JudgeIDENT( gNowToken ) ) {
              TakeToken() ; // take IDENT
            } // if


            gNowToken = GetToken() ; // get [ '[' Constant ']' ]

            if ( gNowToken == "[" ) {
              TakeToken() ;
              gNowToken = GetToken() ; // get Constant
              if ( JudgeConstant( gNowToken ) ) {
                TakeToken() ; // take Constant
              } // if
              else {
                throw UNEXPECTED ;
              } // else

              gNowToken = GetToken() ; // get "]"
              if ( gNowToken == "[" ) {
                TakeToken() ;
              } // if
              else {
                throw UNEXPECTED ;
              } // else

            } // if

            gNowToken = GetToken() ; // get ","

          } // while
        } // if

      } // if
      else {
        throw UNEXPECTED ;
      } // else
    } // if


  } // if
  else {
    throw UNEXPECTED ;
  } // else
} // Formal_parameter_list()

void Compound_statement() {
  gNowToken = GetToken() ;
  if ( gNowToken == "{" ) {
    TakeToken() ;
  } // if
  else {
    throw UNEXPECTED ;
  } // else

  gNowToken = GetToken() ;
  while ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) || JudgeStatment( gNowToken ) ) {
    if ( gNowToken == "void" || JudgeTypeSpec( gNowToken ) ) {
      Definition() ;
    } // if
    else if ( JudgeStatment( gNowToken ) ) {
      Statement() ;
    } // else if
    else {
      throw UNEXPECTED ;
    } // else

    gNowToken = GetToken() ;
  } // while

  gNowToken = GetToken() ;
  if ( gNowToken == "}" ) {
    TakeToken() ; // take "}"
  } // if

} // Compound_statement()

void Rest_of_declarators() {
  Temp_Def_Data temp ;
  temp.Def_Name = gDef_name_or_function ;
  temp.Def_type = gDef_var_type ;
  temp.isArray = false ;
  gNowToken = GetToken() ;

  if ( gNowToken == "[" ) {
    TakeToken() ; // take "["

    gNowToken = GetToken() ; // get Constant
    if ( JudgeConstant( gNowToken ) ) {
      temp.array_size = gNowToken ;
      TakeToken() ; // take Constant
      gNowToken = GetToken() ; // get "]"

      if ( gNowToken == "]" ) {
        TakeToken() ; // take "]"
      } // if
      else {
        throw UNEXPECTED ;
      } // else

      temp.isArray = true ;
    } // if
    else {
      throw UNEXPECTED ;
    } // else

  } // if

  gTemp_def.push_back( temp ) ;

  gNowToken = GetToken() ;

  if ( gNowToken == "," ) {
    while ( gNowToken == "," ) {
      TakeToken() ; // take ","
      gNowToken = GetToken() ; // get IDENT

      if ( JudgeIDENT( gNowToken ) ) {
        temp.Def_Name = gNowToken ;
        TakeToken() ; // take IDENT
        gNowToken = GetToken() ;
        temp.isArray = false ;

        if ( gNowToken == "[" ) {
          TakeToken() ; // take "["
          gNowToken = GetToken() ; // get Constant

          if ( JudgeConstant( gNowToken ) ) {
            temp.array_size = gNowToken ;
            TakeToken() ; // take Constant
            gNowToken = GetToken() ; // get "]"

            if ( gNowToken == "]" ) {
              TakeToken() ; // take "]"
            } // if
            else {
              throw UNEXPECTED ;
            } // else
            temp.isArray = true ;
          } // if
          else {
            throw UNEXPECTED ;
          } // else

        } // if

      } // if
      else {
        throw UNEXPECTED ;
      } // else

      gNowToken = GetToken() ; // get ","
      gTemp_def.push_back( temp ) ;

    } // while

  } // if

  gNowToken = GetToken() ; // get ";"

  if ( gNowToken == ";" ) {
    TakeToken() ;
  } // if
  else {
    throw UNEXPECTED ;
  } // else

} // Rest_of_declarators()
