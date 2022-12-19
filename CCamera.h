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

    // カメラの更新　ステージの数を入れる
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

    // カメラをプレイヤーの高さに合わて行く ※初期化
    void PlayerChase(int end_pos)
    {
        m_camera_y_move_flg = true;
        m_start_camera_y_pos = m_camera_lookat.y;
        m_start_camera_y_eye = m_camera_eye.y;
        m_end_camera_y_pos = end_pos * 20.0f;
        m_end_camera_y_eye = 180.0f + end_pos * 20.0f;
        m_camera_y_move_time = 0;
    }
    // カメラをプレイヤーの高さに合わせに行く ※移動
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


    XMFLOAT3 m_camera_eye;              // カメラの位置
    XMFLOAT3 m_camera_lookat;          // カメラの注視点

    int m_camera_pos;                       // カメラが4方向どこにいるか
    int m_camera_move_time;              // カメラの回転の時間
    XMFLOAT3 m_start_camera_pos;    // カメラの回転開始位置
    XMFLOAT3 m_end_camera_pos;      // カメラの回転終点位置

    bool m_camera_move_flg;             // カメラが回転しているかどうか

    int m_camera_y_move_time;          // カメラの縦方向の移動時間
    int m_start_camera_y_pos;          // カメラの縦の開始位置
    int m_start_camera_y_eye;
    int m_end_camera_y_pos;            // カメラの縦の終点位置
    int m_end_camera_y_eye;
    bool m_camera_y_move_flg;         // カメラが縦に移動しているか

private:
    XMFLOAT4X4		m_Projection;

    XMFLOAT4X4		m_Camera;

    XMFLOAT3		m_Eye;				// カメラ位置
    XMFLOAT3		m_Lookat;			// 注視点
    XMFLOAT3		m_Up;				// 上向きベクトル

    float			m_near;
    float			m_Aspect;
    float			m_Fov;
    float			m_far;
};