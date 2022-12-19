#include	<directxmath.h>
#include	"Memory.h"

using namespace DirectX;

class CCamera
{
    CCamera()
    {
    }
public:
    CCamera(const CCamera &) = delete;
    CCamera & operator=(const CCamera &) = delete;
    CCamera(CCamera &&) = delete;
    CCamera & operator=(CCamera &&) = delete;

    static CCamera * GetInstance()
    {
        static CCamera instance;
        return &instance;
    }

    void Init(float nearclip , float farclip , float fov ,
        float width , float height ,
        XMFLOAT3 eye , XMFLOAT3 lookat , XMFLOAT3 up)
    {

        SetProjection(nearclip , farclip , fov , width , height);
        SetCamera(eye , lookat , up);
    }

    void SetNear(float nearclip)
    {
        m_near = nearclip;
    }

    void SetFar(float farclip)
    {
        m_far = farclip;
    }

    void SetFov(float fov)
    {
        m_Fov = fov;
    }

    void SetAspect(float width , float height)
    {
        m_Aspect = width / height;
    }

    void SetProjection(float nearclip , float farclip , float fov , float width , float height)
    {
        SetNear(nearclip);
        SetFar(farclip);
        SetFov(fov);
        SetAspect(width , height);
        CreateProjectionMatrix();
    }

    void SetCamera(const XMFLOAT3 & eye , const XMFLOAT3 & lookat , const XMFLOAT3 & up)
    {

        SetEye(eye);
        SetLookat(lookat);
        SetUp(up);
        CreateCameraMatrix();
    }

    void SetEye(const XMFLOAT3 & eye)
    {
        m_Eye = eye;
    }

    void SetLookat(const XMFLOAT3 & lookat)
    {
        m_Lookat = lookat;
    }

    void SetUp(const XMFLOAT3 & up)
    {
        m_Up = up;
    }

    void CreateCameraMatrix()
    {
        ALIGN16 XMVECTOR Eye = XMVectorSet(m_Eye.x , m_Eye.y , m_Eye.z , 0.0f);
        ALIGN16 XMVECTOR At = XMVectorSet(m_Lookat.x , m_Lookat.y , m_Lookat.z , 0.0f);
        ALIGN16 XMVECTOR Up = XMVectorSet(m_Up.x , m_Up.y , m_Up.z , 0.0f);

        ALIGN16 XMMATRIX camera;
        camera = XMMatrixLookAtLH(Eye , At , Up);

        XMStoreFloat4x4(&m_Camera , camera);
    }

    void CreateProjectionMatrix()
    {

        ALIGN16 XMMATRIX projection;

        projection = XMMatrixPerspectiveFovLH(m_Fov , m_Aspect , m_near , m_far);

        XMStoreFloat4x4(&m_Projection , projection);

    }

    const XMFLOAT4X4 & GetCameraMatrix()
    {
        return m_Camera;
    }

    const XMFLOAT4X4 & GetProjectionMatrix()
    {
        return m_Projection;
    }

    float GetFov() const
    {
        return m_Fov;
    }

    const XMFLOAT3 & GetEye() const
    {
        return m_Eye;
    }

    const XMFLOAT3 & GetLookat() const
    {
        return m_Lookat;
    }

    const XMFLOAT3 & GetUp() const
    {
        return m_Up;
    }

    // �J�����̍X�V�@�X�e�[�W�̐�������
    void Update(int stage_num)
    {
        if (CCamera::GetInstance()->m_camera_move_time == 11)
        {
            switch (m_camera_pos)
            {
                case 1:
                    m_start_camera_pos = m_camera_eye;
                    m_end_camera_pos = { ((float) stage_num - 1.0f) * -50.0f , m_camera_eye.y , ((float) stage_num - 1.0f) * -10.0f };
                    m_camera_move_time = 0;
                    m_camera_pos++;
                    break;
                case 2:
                    m_start_camera_pos = m_camera_eye;
                    m_end_camera_pos = { ((float) stage_num - 1.0f) * 10.0f , m_camera_eye.y , ((float) stage_num - 1.0f) * 50.0f };
                    m_camera_move_time = 0;
                    m_camera_pos++;
                    break;
                case 3:
                    m_start_camera_pos = m_camera_eye;
                    m_end_camera_pos = { (float) stage_num * 50.0f , m_camera_eye.y , ((float) stage_num - 1.0f) * -10.0f };
                    m_camera_move_time = 0;
                    m_camera_pos++;
                    break;
                case 4:
                    m_start_camera_pos = m_camera_eye;
                    m_end_camera_pos = { ((float) stage_num - 1.0f) * 10.0f , m_camera_eye.y , (float) stage_num * -50.0f };
                    m_camera_move_time = 0;
                    m_camera_pos = 1;
                    break;
            }
        }

        if (m_camera_move_time < 11)
        {
            m_camera_eye.x = m_start_camera_pos.x * (1.0f - (m_camera_move_time / 10.0f))
                + m_end_camera_pos.x * (m_camera_move_time / 10.0f);
            m_camera_eye.z = m_start_camera_pos.z * (1.0f - (m_camera_move_time / 10.0f))
                + m_end_camera_pos.z * (m_camera_move_time / 10.0f);
            m_camera_move_time++;

            SetCamera(m_camera_eye , m_camera_lookat , { 0.0f,1.0f,0.0f });

            if (m_camera_move_time == 11)
            {
                m_camera_move_flg = false;
            }
        }
    }

    // �J�������v���C���[�̍����ɍ���čs�� ��������
    void PlayerChase(int end_pos)
    {
        m_camera_y_move_flg = true;
        m_start_camera_y_pos = m_camera_lookat.y;
        m_start_camera_y_eye = m_camera_eye.y;
        m_end_camera_y_pos = end_pos * 20.0f;
        m_end_camera_y_eye = 180.0f + end_pos * 20.0f;
        m_camera_y_move_time = 0;
    }
    // �J�������v���C���[�̍����ɍ��킹�ɍs�� ���ړ�
    void PlayerChase()
    {
        if (m_camera_y_move_time < 11)
        {
            m_camera_eye.y = m_start_camera_y_eye * (1.0f - (m_camera_y_move_time / 10.0f))
                + m_end_camera_y_eye * (m_camera_y_move_time / 10.0f);

            m_camera_lookat.y = m_start_camera_y_pos * (1.0f - (m_camera_y_move_time / 10.0f))
                + m_end_camera_y_pos * (m_camera_y_move_time / 10.0f);
            m_camera_y_move_time++;

            SetEye(m_camera_eye);
            SetLookat(m_camera_lookat);
            CCamera::GetInstance()->CreateCameraMatrix();

            if (m_camera_y_move_time == 11)
            {
                m_camera_y_move_flg = false;
            }
        }
    }


    XMFLOAT3 m_camera_eye;              // �J�����̈ʒu
    XMFLOAT3 m_camera_lookat;          // �J�����̒����_

    int m_camera_pos;                       // �J������4�����ǂ��ɂ��邩
    int m_camera_move_time;              // �J�����̉�]�̎���
    XMFLOAT3 m_start_camera_pos;    // �J�����̉�]�J�n�ʒu
    XMFLOAT3 m_end_camera_pos;      // �J�����̉�]�I�_�ʒu

    bool m_camera_move_flg;             // �J��������]���Ă��邩�ǂ���

    int m_camera_y_move_time;          // �J�����̏c�����̈ړ�����
    int m_start_camera_y_pos;          // �J�����̏c�̊J�n�ʒu
    int m_start_camera_y_eye;
    int m_end_camera_y_pos;            // �J�����̏c�̏I�_�ʒu
    int m_end_camera_y_eye;
    bool m_camera_y_move_flg;         // �J�������c�Ɉړ����Ă��邩

private:
    XMFLOAT4X4		m_Projection;

    XMFLOAT4X4		m_Camera;

    XMFLOAT3		m_Eye;				// �J�����ʒu
    XMFLOAT3		m_Lookat;			// �����_
    XMFLOAT3		m_Up;				// ������x�N�g��

    float			m_near;
    float			m_Aspect;
    float			m_Fov;
    float			m_far;
};