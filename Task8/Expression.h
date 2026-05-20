#ifndef TASK8_EXPRESSION_H
#define TASK8_EXPRESSION_H

#include <iostream>
#include <map>
#include <string>


class ExpressionFactory;

class Expression {
public:
    virtual ~Expression() = default;
    virtual void print(std::ostream& out) const = 0;
    virtual int calculate(const std::map<std::string, int>& context) const = 0;
    virtual void retain() {}
    virtual void release() { delete this; }
};

inline std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    expr.print(os);
    return os;
}

class FlyweightExpression : public Expression {
public:
    FlyweightExpression(ExpressionFactory* factory, bool immortal = false)
        : factory_(factory), immortal_(immortal), refCount_(0) {}

    void retain() override {
        ++refCount_;
    }

    void release() override;

protected:
    ExpressionFactory* factory_;
    bool immortal_;
    int refCount_;

public:
    bool isImmortal() const {
        return immortal_;
    }
};


class Constant final : public FlyweightExpression {
public:
    Constant(ExpressionFactory* factory, int value, bool immortal = false)
        : FlyweightExpression(factory, immortal), value_(value) {}

    void print(std::ostream& out) const override {
        out << value_;
    }

    int calculate(const std::map<std::string, int>&) const override {
        return value_;
    }

    int value() const {
        return value_;
    }

private:
    int value_;
};


class Variable final : public FlyweightExpression {
public:
    Variable(ExpressionFactory* factory, std::string name)
        : FlyweightExpression(factory, false), name_(std::move(name)) {}

    void print(std::ostream& out) const override {
        out << name_;
    }

    int calculate(const std::map<std::string, int>& context) const override {
        auto it = context.find(name_);
        if (it == context.end()) {
            throw std::runtime_error("Undefined variable: " + name_);
        }
        return it->second;
    }

    const std::string& name() const {
        return name_;
    }

private:
    std::string name_;
};

class BinaryOperator : public Expression {
public:
    BinaryOperator(Expression* left, Expression* right)
        : left_(left), right_(right) {
        if (!left_ || !right_) {
            throw std::invalid_argument("Binary operator requires two operands");
        }
        left_->retain();
        right_->retain();
    }

    ~BinaryOperator() override {
        left_->release();
        right_->release();
    }

    void print(std::ostream& out) const override {
        out << '(';
        left_->print(out);
        out << ' ' << symbol() << ' ';
        right_->print(out);
        out << ')';
    }

protected:
    virtual const char* symbol() const = 0;

    Expression* left_;
    Expression* right_;
};

class Addition final : public BinaryOperator {
public:
    Addition(Expression* left, Expression* right)
        : BinaryOperator(left, right) {}

    int calculate(const std::map<std::string, int>& context) const override {
        return left_->calculate(context) + right_->calculate(context);
    }

protected:
    const char* symbol() const override {
        return "+";
    }
};

class Subtraction final : public BinaryOperator {
public:
    Subtraction(Expression* left, Expression* right)
        : BinaryOperator(left, right) {}

    int calculate(const std::map<std::string, int>& context) const override {
        return left_->calculate(context) - right_->calculate(context);
    }

protected:
    const char* symbol() const override {
        return "-";
    }
};

class Multiplication final : public BinaryOperator {
public:
    Multiplication(Expression* left, Expression* right)
        : BinaryOperator(left, right) {}

    int calculate(const std::map<std::string, int>& context) const override {
        return left_->calculate(context) * right_->calculate(context);
    }

protected:
    const char* symbol() const override {
        return "*";
    }
};

class Division final : public BinaryOperator {
public:
    Division(Expression* left, Expression* right)
        : BinaryOperator(left, right) {}

    int calculate(const std::map<std::string, int>& context) const override {
        int divisor = right_->calculate(context);
        if (divisor == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left_->calculate(context) / divisor;
    }

protected:
    const char* symbol() const override {
        return "/";
    }
};

#endif // TASK8_EXPRESSION_H
