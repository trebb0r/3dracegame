#ifndef FPS_H
#define FPS_H


class FPS
{
	private:
		FPS(){}

	public:
		static void update();

	private:
		static float startTime;
		static int count;
};

#endif // FPS_H
