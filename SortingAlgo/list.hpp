#pragma once

class List {
    public:
    virtual void insert(int) = 0;
    virtual int get(int) = 0;
    virtual void print() = 0;
    virtual int size() = 0;
};