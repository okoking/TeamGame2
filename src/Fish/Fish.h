#pragma once

// ���̍ő吔
const int FISH_MAX_NUM = 10;

// ���̉摜�p�X
const char FISH_PATH[] = { "data/play/fish.png" };
const char CAUGHT_FISH_PATH[] = {"data/play/uokage.png"};

//���_���Z�̉摜�p�X
const char SCORE_IMAGE_PATH[] = { "data/play/addScore.png" };

//���_���Z�̉摜�p�X

// ���̑��x
const float FISH_SPEED = 5.0f;

// ���摜�̃T�C�Y
const float FISH_X_SIZE = 100.0;
const float FISH_Y_SIZE = 42.0;

//���o���ő厞��
const int FISH_POP_TIME = 1;

// ���̉摜�̎��
enum FISH_IMAGE_TYPE {
	IMAGE_TYPE_NORMAL = 0,
	IMAGE_TYPE_CAUGHT,

	IMAGE_TYPE_NUM,
};
// Fish�N���X
class Fish {
private:
	int handle[IMAGE_TYPE_NUM][FISH_MAX_NUM];								 // ���摜�n���h��
	float _X[FISH_MAX_NUM], _Y[FISH_MAX_NUM];				 // ���݂̍��W
	float _SaveX[FISH_MAX_NUM], _SaveY[FISH_MAX_NUM];		 // �ړ���̍��W
	int Poptime;											 //�����o�Ă���܂ł̎���
	float countTime;

	int fishSpeed[FISH_MAX_NUM];	//�ړ����x

	bool isLeft[FISH_MAX_NUM];								 // ���������Ă��邩�ǂ���
	bool isActive[FISH_MAX_NUM];							 //	�����Ă��邩�ǂ���
	bool isCaught[FISH_MAX_NUM];							 // �������Ă��邩�ǂ���

	float angle[FISH_MAX_NUM];	//���̐i�s����

	int CaughtNum; // ���C�ނ�Ă��邩

	bool fishingChance;

	//���_============================
	int scoreImageHandle;	//���_���Z�摜�n���h��
	int scoreAddY;	//���_���Z�̍��W(�ω����������Z)
	int scoreFade;	//���_���Z�̓����x
	bool addScore;	//���_���Z���o���s�t���O


public:

	Fish(); // �R���X�g���N�^

	// ���W�ύX�p(����:X���W,Y���W,�z��ԍ�)
	void Setpos(float X, float Y,int FishIndex) 
	{
		_SaveX[FishIndex] = X;
		_SaveY[FishIndex] = Y;
	}

	// X���W�擾�p(����:�z��ԍ�)
	float GetXPos(int FishIndex) { return _X[FishIndex]; }
	// Y���W�擾�p(����:�z��ԍ�)
	float GetYPos(int FishIndex) { return _Y[FishIndex]; }

	// �ړ����X���W�擾�p(����:�ړ���̍��W,�z��ԍ�)
	void GetSaveXPos(float X,int FishIndex) { _SaveX[FishIndex] = X; }

	// �ړ����Y���W�擾�p(����:�ړ���̍��W,�z��ԍ�)
	void GetSaveYPos(float Y,int FishIndex) { _SaveY[FishIndex] = Y; }

	//���A�[�ɓ���������̍��W��ݒ�
	void SetHitUpdatePosX(float X, int FishIndex) { _X[FishIndex] -= X; }
	void SetHitUpdatePosY(float Y, int FishIndex) { _Y[FishIndex] -= Y; }

	//���������Ă��邩�ǂ����̃t���O�擾�p
	bool GetIsActive(int FishIndex) { return isActive[FishIndex]; }

	// ���W�X�V�p(����:�z��ԍ�)
	void UpdatePos();
	 
	// isCaught�ύX�p(����:�z��ԍ�,�ύX��)
	void SetisCaught(int FishIndex, bool _isCaught);

	// isCaught�擾�p�֐�
	bool GetisCaught(int FishIndex) { return isCaught[FishIndex]; }

	// ������
	void Init();

	// �摜���[�h
	void Load();

	// �ʏ폈��(����:���A�[�̍��W)
	void Step(float lureX, float lureY, bool lureIsUse, bool lureIsCaught);

	// �摜�`��
	void Draw();

	// �I������
	void Fin();

	//�ړ�����
	void Move(float lureX, float lureY, bool lureIsUse, bool lureIsCaught);

	//�o�����ԊǗ�����
	void SetPopTime();

	//���o��
	void Pop();

	//�����������Ƃ�
	void Caught(float lureX, float lureY);

	//X���W�ɉ��Z
	void AddPosX(int index, float set) { _X[index] += set; }
	//���E���擾
	bool GetIsLeft(int index) { return isLeft[index]; }
	//�����t���O���擾
	void SetIsActive(int index, bool set) { isActive[index] = set; }

	//���W���w��
	void SetPosX(int index, float set) { _X[index] = set; }
	void SetPosY(int index, float set) { _Y[index] = set; }

	//�ނ������̐����擾
	int GetCaughtNum() { return CaughtNum; }

	//���_���Z�̓���
	void ScoreAddMove();
};

//hit�`�����X��ԃt���O
extern bool fishChance;

extern Fish fish;