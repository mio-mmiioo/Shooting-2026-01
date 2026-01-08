#pragma once
#include "../MyLibrary/Object3D.h"

enum CAM_STATE
{
	FIRST,	// 一人称視点
	THIRD,	// 三人称視点
	FIX,	// 固定カメラ
	MAX_CAM_STATE
};

class Camera : public Object3D
{
public:
	Camera();
	~Camera();
	void Update() override;
	void SetPlayerPosition(const Transform& transform);

private:
	void FirstCamera();		// 一人称カメラ
	void ThirdCamera();		// 三人称カメラ
	void FixCamera();		// 固定カメラ
	void ChangeCamera();	// カメラの切り替え
	void ImGuiInput(); // 開発時のみ使用する 

	Transform player_;		// プレイヤーの情報
	int mouseX_;			// マウスのx座標
	int mouseY_;			// マウスのy座標
	int prevMouseX_;		// 前のマウスの座標x
	int prevMouseY_;		// 前のマウスの座標y

	CAM_STATE state_;	// カメラの状態

	VECTOR3 cameraPosition_; // 最終的にセットされる視点の位置
	VECTOR3 targetPosition_; // 最終的にセットされる注視点の位置
	VECTOR3 fixAddPosition_; // 固定カメラを移動させるときに使用する、加算された位置

	int wheelRot_; // マウスホイール
};
