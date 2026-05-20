#include "ExpressionFactory.h"
#include <iostream>
#include <map>

int main() {
    ExpressionFactory factory;

    Constant* c2 = factory.createConstant(2);
    Variable* x = factory.createVariable("x");
    Addition* expression = new Addition(c2, x);

    std::map<std::string, int> context;
    context["x"] = 3;

    std::cout << "Expression: " << *expression << '\n';
    std::cout << "Value: " << expression->calculate(context) << '\n';

    delete expression;

    std::cout << "---" << '\n';

    Constant* c5 = factory.createConstant(5);
    Constant* c2b = factory.createConstant(2);
    Variable* x2 = factory.createVariable("x");
    Variable* y = factory.createVariable("y");
git status
    Expression* complexExpression = new Subtraction(
        new Multiplication(c2b, new Addition(x2, c5)),
        new Division(y, c2b)
    );

    context["y"] = 10;

    std::cout << "Expression: " << *complexExpression << '\n';
    std::cout << "Value: " << complexExpression->calculate(context) << '\n';

    delete complexExpression;

    return 0;
}
