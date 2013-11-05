#ifndef SAMPLE_H_
#define SAMPLE_H_

class Sample {
  public:
    int x, y;

    Sample() {
    }

    Sample(int x, int y) {
      this->x = x;
      this->y = y;
    }

	bool operator==(const Sample& s) const {
		return x==s.x && y==s.y;
	}
};

#endif
