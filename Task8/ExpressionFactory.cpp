#include "ExpressionFactory.h"
#include <stdexcept>



void FlyweightExpression::release() {
    if (isImmortal()) {
        if (refCount_ > 0)
            --refCount_;
        return;
    }

    if (--refCount_ > 0) 
        return;

    if (!factory_) {
        delete this;
        return;
    }

    if (auto constant = dynamic_cast<Constant*>(this))
        factory_->removeConstant(constant);
    
    else if (auto variable = dynamic_cast<Variable*>(this))
        factory_->removeVariable(variable);
    
    else 
        delete this;
}


ExpressionFactory::ExpressionFactory() {
    for (int i = -5; i <= 256; ++i) {
        constants_[i] = new Constant(this, i, true);
    }
}

ExpressionFactory::~ExpressionFactory() {
    for (auto& entry : constants_) {
        delete entry.second;
    }

    for (auto& entry : variables_) {
        delete entry.second;
    }
}


Constant* ExpressionFactory::createConstant(int value) {
    auto it = constants_.find(value);
    if (it != constants_.end()) {
        it->second->retain();
        return it->second;
    }

    Constant* constant = new Constant(this, value, false);
    constant->retain();
    constants_.emplace(value, constant);
    return constant;
}

Variable* ExpressionFactory::createVariable(const std::string& name) {
    auto it = variables_.find(name);
    if (it != variables_.end()) {
        it->second->retain();
        return it->second;
    }

    Variable* variable = new Variable(this, name);
    variable->retain();
    variables_.emplace(variable->name(), variable);
    return variable;
}

void ExpressionFactory::releaseConstant(Constant* constant) {
    if (constant) {
        constant->release();
    }
}

void ExpressionFactory::releaseVariable(Variable* variable) {
    if (variable)
        variable->release();
}

void ExpressionFactory::removeConstant(Constant* constant) {
    if (!constant) {
        return;
    }

    if (constant->isImmortal()) {
        return;
    }

    constants_.erase(constant->value());
    delete constant;
}

void ExpressionFactory::removeVariable(Variable* variable) {
    if (!variable) {
        return;
    }

    variables_.erase(variable->name());
    delete variable;
}
