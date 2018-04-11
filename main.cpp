# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <string>
# include <vector>
# include <ctype.h>
# include <iomanip>


using namespace std;

// ======================Data Struct==============================
enum Error_type{ UNRECOGNIZED, UNDEFINED, UNEXPECTED, ERROR };

struct Identify_Data{
  string identify_Name ;
  double identify_value ;
  bool isFloat ;
} ;

// ===============================================================

// ======================global var===============================
string gNowToken ;
string gBoolAns ;
vector<Identify_Data> gId ;
int gTestNum = 0 ;
bool gChange = false ;
bool gIsBoolOP = false ;
bool gQuit = false ;
bool gIsFloat = false ;
char gUnknowChar ;
// ===============================================================

// =======================use for get token=======================
string GetToken() ;
void SkipExitChar() ;
string ReadConstant() ;
string ReadIdent() ;
string ReadOPAndComment() ;
bool IsFloat() ;
void TakeToken() ;
void ReadAfterError() ;
// ===============================================================

int main() {
    while ( gNowToken != "quit1" ) {
      gNowToken.clear() ;
      gNowToken = GetToken() ;
      cout << gNowToken << endl ;
    } // if


    return 0;
} // main()

string GetToken() {

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
        cin.getline( comment , 500 ) ;
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
    } // while

  } // else

} // SkipExitChar()

