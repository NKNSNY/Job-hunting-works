#pragma once
#include "gameobject.h"
#include "CModel.h"
#include"player_anim.h"
#include "player_anim_data.h"
#include "player_chip.h"

class Player :public GameObject
{
public:

    // �I�u�W�F�N�g��
    enum PLAYERPARTS
    {
        HIP ,			// ��
        BODY ,			// ����
        HEAD ,		// ��
        ARMR1 ,		// �E��r
        ARML1 ,		// ����r
        LEGR1 ,		// �E������
        LEGL1 ,		// ��������
        ARMR2 ,
        ARML2 ,
        LEGR2 ,
        LEGL2 ,
        ARMR3 ,
        ARML3 ,
        LEGR3 ,
        LEGL3 ,
        NONE ,			// �Ȃ�
        END ,			// �f�[�^�Ȃ�
        PARTSMAX
    };

    // �\���̌^�^�O
    struct	PlayerInitData
    {
        Player::PLAYERPARTS		ParentObjectNo;		// �e�I�u�W�F�N�g�m��
        Player::PLAYERPARTS		ModelNo;					// ���f���ԍ�
        DirectX::XMFLOAT3	FirstPosition;		// �ŏ��̈ʒu
        DirectX::XMFLOAT3	FirstAngle;			// �ŏ��̊p�x
    };

    // �v���C���[�̃��f�������X�g
    struct	PlayerModelData
    {
        Player::PLAYERPARTS		ModelNo;					// ���f���ԍ�
        const char * XfileName;										// �w�t�@�C����
    };

    // �����z�u�f�[�^
    static PlayerInitData	ObjectInitData [];

    // ���f���t�@�C�������X�g
    static PlayerModelData			XFileData [];

    // ���f���Z�b�g
    void SetModel(CModel * p , int idx)
    {
        m_models [idx] = p;
    }

    // �I�[�o�[���[�h
    bool Init();

    bool Init(int stage_width , int player_y);
    void Draw();
    void Update(int camera_pos);
    void Finalize();

    // �X�e�[�W�̍����̏����Z�b�g
    void SetPlayerStageTop(int y , int x , int stage_top);
    // �X�e�[�W���o��邩�ǂ����Z�b�g
    void SetClimbFlg(int y , int x , bool fall_flg);

    PlayerAnimation m_player_anim;          // �v���C���[�̃A�j���[�V�����֘A

    PlayerChip m_player_chip;                  // �v���C���[���ǂ��ɂ��邩

    int m_player_camera_pos;                   // �J��������̃v���C���[�̏��
    int m_player_stage_width;                  // �X�e�[�W�̕�
    int m_player_hight;                           // �v���C���[�̌��݂̍���

    bool m_player_climb_flg5 [7][7];          // �v���C���[���o��邩

    int m_walk_time;                               // ��������
    DirectX::XMFLOAT3 m_walk_start_pos;   // �����n�߂�ꏊ
    DirectX::XMFLOAT3 m_walk_end_pos;     // �����I���ꏊ
    DirectX::XMFLOAT3 m_move_direction;   // �ړ���

    int m_player_direction;                       // �v���C���[�̌���
    int m_standby_direction;                     // �V�t�g�����������̃v���C���[�̌���

    bool m_player_qube_move_flg;              // �v���C���[���L���[�u�𓮂�������

    int m_player_hp;                               // �v���C���[��HP

    bool m_player_crush_flg;                     // �v���C���[���ׂ��ꂽ���ǂ���

private:
    void UpdateLocalpose();				// ���[�J���|�[�Y���X�V����
    void CaliculateParentChildMtx();	// �e�q�֌W���l�������s����쐬
    static bool m_modelloadflag;		// ���f����ǂݍ��񂾂��ǂ���
    CModel * m_models [PLAYERPARTS::PARTSMAX];
    DirectX::XMFLOAT4X4			m_mtxlocalpose [PARTSMAX];	// �����̂��Ƃ������l�����s��
    DirectX::XMFLOAT4X4			m_mtxParentChild [PARTSMAX];	// �e�q�֌W���l�������s��

    float						m_speed = 0.0f;				// �X�s�[�h
    DirectX::XMFLOAT3			m_angle;					// ��]�p

    // �v���C���[�̓�������
    void MovePlayer(CharChipInt3 move_direction);

    //int m_idx = 0;

};