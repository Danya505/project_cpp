#ifndef TASK8_EXPRESSION_FACTORY_H
#define TASK8_EXPRESSION_FACTORY_H

#include "Expression.h"
#include <map>
#include <string>


class ExpressionFactory {
public:
    ExpressionFactory();
    ~ExpressionFactory();

    Constant* createConstant(int value);
    Variable* createVariable(const std::string& name);

    void releaseConstant(Constant* constant);
    void releaseVariable(Variable* variable);

private:
    friend class FlyweightExpression;

    void removeConstant(Constant* constant);
    void removeVariable(Variable* variable);

    std::map<int, Constant*> constants_;
    std::map<std::string, Variable*> variables_;
};

#endif // TASK8_EXPRESSION_FACTORY_H
