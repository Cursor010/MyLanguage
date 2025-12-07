#include <bits/stdc++.h>
using namespace std;
const int number_re = 0;
bool is_literal() {

}
pair<string,string> give_token() {
  return {};
}
void Expr();
void AssignExpr();
void ORExpr();
void AndExpr();
void EqualExpr();
void AddExpr();
void MullExpr();
void UnExpr();
void PostfixExpr();
void Index();
void Prime();
void NameOrCall();
void CallParamList();
void go_to_next() {}
pair<string,string> token;
void Type() {
  if (token.first == "bool" || token.first == "char" || token.first == "int" || token.first == "float") {
    go_to_next();
    return;
  }
  throw number_re;
}
void Name1() {
  if (token.second != "IDENTIFIER") {
    go_to_next();
    throw number_re;
  }
}
// ================= NumberLiteral =================
void NumberLiteral() {
    if (token.second == "INTEGER" || token.second == "FLOAT") {
        go_to_next();
    } else {
        throw number_re;
    }
}

// ================= Prime =================
void Prime() {
    if (token.second == "INTEGER" || token.second == "FLOAT") {
        NumberLiteral();
    } else if (token.second == "IDENTIFIER") {
        NameOrCall();
    } else if (token.first == "(") {
        go_to_next();
        Expr();
        if (token.first != ")") throw number_re;
        go_to_next();
    } else {
        throw number_re;
    }
}

// ================= Index =================
void Index() {
    if (token.first == "[") {
        go_to_next();
        Expr();
        if (token.first != "]") throw number_re;
        go_to_next();
    }
}

// ================= PostfixExpr =================
void PostfixExpr() {
    Prime();
    if (token.first == "[") {
        Index();
    }
}

// ================= UnExpr =================
void UnExpr() {
    if (token.first == "+" || token.first == "-" || token.first == "!") {
        go_to_next();
    }
    PostfixExpr();
}

// ================= MullExpr =================
void MullExpr() {
    UnExpr();
    while (token.first == "*" || token.first == "/" || token.first == "%") {
        go_to_next();
        UnExpr();
    }
}

// ================= AddExpr =================
void AddExpr() {
    MullExpr();
    while (token.first == "+" || token.first == "-") {
        go_to_next();
        MullExpr();
    }
}

// ================= EqualExpr =================
void EqualExpr() {
    AddExpr();
    while (token.first == "==" || token.first == "!=" || token.first == "<" || token.first == ">" ||
           token.first == "<=" || token.first == ">=") {
        go_to_next();
        AddExpr();
    }
}

// ================= AndExpr =================
void AndExpr() {
    EqualExpr();
    while (token.first == "&&") {
        go_to_next();
        EqualExpr();
    }
}

// ================= ORExpr =================
void ORExpr() {
    AndExpr();
    while (token.first == "||") {
        go_to_next();
        AndExpr();
    }
}

// ================= AssignExpr =================
void AssignExpr() {
    ORExpr();
    if (token.first == "=") {
        go_to_next();
        AssignExpr();
    }
}

// ================= Expr =================
void Expr() {
    AssignExpr();
    while (token.first == ",") {
        go_to_next();
        AssignExpr();
    }
}

// ================= NameOrCall =================
void NameOrCall() {
    if (token.second != "IDENTIFIER") throw number_re;
    go_to_next();
    if (token.first == "(") {
        go_to_next();
        CallParamList();
        if (token.first != ")") throw number_re;
        go_to_next();
    }
}

// ================= CallParamList =================
void CallParamList() {
    if (token.first != ")") { // проверяем, есть ли хотя бы один параметр
        AssignExpr();
        while (token.first == ",") {
            go_to_next();
            AssignExpr();
        }
    }
}

void TypeName() {
  Type();
  Name1();
  while (token.first != ";") {
    if (token.first != ",") {
      throw number_re;
    }
    go_to_next();
    Name1();
  }
}
void Assign() {
  if (token.first != "=") throw number_re;
  go_to_next();
  if (token.first != "{") throw number_re;
  go_to_next();

  // Должно идти хотя бы одно выражение
  AssignExpr();

  // Дополнительные выражения через запятую
  while (token.first == ",") {
    go_to_next();
    AssignExpr();
  }

  // Закрывающая фигурная скобка
  if (token.first != "}") throw number_re;
  go_to_next();
}
void IndexInit() {
  go_to_next();
  Expr();
  if (token.first != "]") throw number_re;
  go_to_next();
}
void Array1() {
  if (token.second != "IDENTIFIER") throw number_re;
  go_to_next();
  if (token.first == "=") {
    Assign();
  } else if (token.first == "[") {
    IndexInit();
  }
}

void ArrayInit() {
  Array1();
  while (token.first == ",") {
    go_to_next();
    Array1();
  }
}

void Array() {
  if (token.first != "<") {
    throw number_re;
  }
  go_to_next();
  Type();
  if (token.first != ">") {
    throw number_re;
  }
  go_to_next();
  ArrayInit();
}
void String1() {
  if (token.second != "IDENTIFIER") throw number_re;
  go_to_next();
  if (token.first == "=") {
    go_to_next();
    if (token.second != "STRING_LITERAL") throw number_re;
    go_to_next();
  }
}

void StringInit() {
  String1();
  while (token.first == ",") {
    go_to_next();
    String1();
  }
}

void String() {
  StringInit();
}

void FuncParam() {
  Type();
  if (token.second != "IDENTIFIER") throw number_re;
  go_to_next();
}
void Block() {

}
void FuncParamList() {
  if (token.first == ")")return;
  FuncParam();
  while (token.first == ",") {
    FuncParam();
  }
}

void Function() {
  if (token.first != "void") Type();
  else go_to_next();
  if (token.second != "IDENTIFIER") throw number_re;
  go_to_next();
  if (token.first != "(") throw number_re;
  go_to_next();
  FuncParamList();
  if (token.first != ")") throw number_re;
  go_to_next();
  Block();
}

void Init() {
  if (token.first == "vector") {
    go_to_next();
    Array();
  }else if (token.first == "string") {
    go_to_next();
    String();
  }else {
    TypeName();
  }
  if (token.first != ";") throw number_re;
  go_to_next();
}
void IF() {
  if (token.first != "if") throw number_re;
  go_to_next();

  if (token.first != "(") throw number_re;
  go_to_next();

  Expr();

  if (token.first != ")") throw number_re;
  go_to_next();
  Block();
  while (token.first == "elif") {
    go_to_next();
    if (token.first != "(") throw number_re;
    go_to_next();
    Expr();
    if (token.first != ")") throw number_re;
    go_to_next();
    Block();
  }
  if (token.first == "else") {
    go_to_next();
    Block();
  }
}
void ForInit() {
  // Пустая альтернатива: если первый токен не INIT и не выражение, ничего не делаем
  if (token.second == "INIT" && token.first != "void") {
    TypeName();
  } else if (token.second == "IDENTIFIER") {
    Expr();
  }
}
void Item2() {

}
void BlockCycle() {
  if (token.first != "{") throw number_re;
  go_to_next();
  while (token.first != "}") {
    Item2();
  }
  go_to_next();
}
void For() {
  if (token.first != "for") throw number_re;
  go_to_next();

  if (token.first != "(") throw number_re;
  go_to_next();

  // [<ForInit>]
  ForInit();

  // ";"
  if (token.first != ";") throw number_re;
  go_to_next();
  // [<Expr>]
  if (token.first != ";") {
    Expr();
  }
  if (token.first != ")") throw number_re;
  go_to_next();
  BlockCycle();
}

void While() {
  if (token.first != "while") throw number_re;
  go_to_next();

  if (token.first != "(") throw number_re;
  go_to_next();

  Expr();

  if (token.first != ")") throw number_re;
  go_to_next();

  BlockCycle();
}

void DoWhile() {
  if (token.first != "do") throw number_re;
  go_to_next();

  BlockCycle();

  if (token.first != "while") throw number_re;
  go_to_next();

  if (token.first != "(") throw number_re;
  go_to_next();

  Expr();

  if (token.first != ")") throw number_re;
  go_to_next();

  if (token.first != ";") throw number_re;
  go_to_next();
}

void Print() {
  if (token.first != "print") throw number_re;
  go_to_next();

  if (token.first != "(") throw number_re;
  go_to_next();

  AssignExpr();
  while (token.first == ",") {
    go_to_next();
    AssignExpr();
  }

  if (token.first != ")") throw number_re;
  go_to_next();
}

void Reg() {
  if (token.first == "if") {
    IF();
  } else if (token.first == "for") {
    For();
  } else if (token.first == "while") {
    While();
  } else if (token.first == "do") {
    DoWhile();
  } else if (token.first == "print") {
    Print();
    if (token.first != ";") throw number_re;
    go_to_next();
  } else if (token.second == "IDENTIFIER" ) {//этого хватит ??
    Expr();
    if (token.first != ";") throw number_re;
    go_to_next();
  } else {
    throw number_re;
  }
}
void Item() {
  token = give_token();
  if (token.first == "def") {
    go_to_next();
    Function();
  }else if (token.second == "INIT" && token.first != "void") {
    Init();
  }else if (token.second == "KEYWORD" || token.first == "IDENTIFIER" || token.first == "INTEGER" || token.first == "FLOAT" || token.first == "STRING_LITERAL") {
    Reg();
  }else {
    throw number_re;
  }
}
void Program() {
  token = give_token();
  while (token.second != "EOF") {
    go_to_next();
    Item();
  }
}
