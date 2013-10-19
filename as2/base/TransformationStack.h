#ifndef TRANSFORMATIONSTACK_H_
#define TRANSFORMATIONSTACK_H_

using namespace std;

class TransformationStack {
  public:
    vector<Transformation> tstack;
    void push(Transformation t) {
      tstack.push_back(t);
    }

    Transformation pop() {
      Transformation t = tstack[tstack.size() - 1];
      tstack.pop_back();
      return t;
    }

    Transformation getCurrentTransformation() {
      Transformation t;
      for(int i = 0; i < tstack.size(); i++) 
        t = t * tstack[i];
      return t;
    }
};

#endif
