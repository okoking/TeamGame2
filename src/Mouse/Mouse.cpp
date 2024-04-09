#include"DxLib.h"
#include"mouse.h"
#include"../Collision/Collision.h"
#include"../MathPlus/MathPlus.h"
#include"../input/input.h"

int zX, zY;

//�摜�p�X
char path[255][50] = {
	"",
};

//������
void Mouse::Init(int pathNum)
{
	Load(pathNum);
	size = 1.0f;
	angle = 0.0f;
	// �}�E�X�̈ʒu���Z�b�g
	//SetMousePoint(1000, 500);
}

//�摜�ǂݍ���
void Mouse::Load(int pathNum)
{
	handle = LoadGraph(path[pathNum]);
}


//�}�E�X�̓���
void Mouse::Move()
{
	zX = x;
	zY = y;
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&zX, &zY);

	x = zX;
	y = zY;
}

//�ʏ폈��
void Mouse::Step()
{
	//����
	Move();

	//���N���b�N�����i�N���b�N���Ƃ��j
	if (Input::Mouse::Push(MOUSE_INPUT_LEFT))
	{
	}
}

//�`��
void Mouse::Draw(int type)
{
	//�ʏ�`��
	if (type == 0)
	{
		DrawRotaGraph(x, y, 1.0f, 0.0f, handle, true);
	}

	//�傫���Ɖ�]�t���`��
	else if (type == 1)
	{
		DrawRotaGraph(x, y, size, angle, handle, true);
	}

	//���߂Ȃ��`��
	else if (type == 2)
	{
		DrawRotaGraph(x, y, 1.0f, 0.0f, handle, false);
	}
}

//�I������
void Mouse::FIn()
{
	//�摜���폜
	DeleteGraph(handle);

	handle = -1;
}

//�}�E�X�����蔻��i�~�`�j
bool Mouse::MouseColli(int Ra, int Rx, int Ry)
{
	if (Collision::Circlr(Ra, 10, Rx, Ry, x, y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�}�E�X�����蔻��i�l�p�j
bool Mouse::MouseColli(int Ax, int Ay, int Aw, int Ah)
{
	if (Collision::Rect(Ax, Ay, Aw, Ah, x-10, y-10, 10, 10))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�g�p���Z�b�g�F�I��false
void Mouse::SetUse(char set)
{
	if (set == '!')
	{
		isUse = false;
	}
	else
	{
		isUse = true;
	}
}
