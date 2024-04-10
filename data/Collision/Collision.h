
#ifndef __COLLISION_H__
#define __COLLISION_H__

class Collision
{
public:
	//四角：X,Yは座標、wが横幅、hが縦幅、画像はDrawGraphで表示してﾈ
	static bool Rect(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
	static bool Rect(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh);

	//円形：Rが半径、X,Yは中央、画像はDrawRotaGraphで表示してﾈ
	static bool Circlr(int Ra, int Rb, int Xa, int Ya, int Xb, int Yb);
};

#endif
