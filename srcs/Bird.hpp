#ifndef BIRD_HPP
#define BIRD_HPP

class Bird {
	public:
		int x, y;

		Bird(int col, int row) : x(col / 4), y(row / 2) {}
		void flap() {
			y += -4;
		}
		void applyGravity() {
			y += 1;
		}
};

#endif
