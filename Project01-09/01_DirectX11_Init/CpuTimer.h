#pragma once
class CpuTimer
{
public:
	CpuTimer();

	float TotalTime() const; //返回从Reset()调用之后经过的时间，不包括暂停期间的
	float DeltaTime() const; //返回帧间隔时间

	void Reset(); //重置计时器
	void Start(); //开始计时器
	void Stop(); //停止计时器
	void Tick(); //每一帧开始的时候调用
	bool IsStopped() const ; //检查计时器是否停止


private:
	double m_SecondsPerCount = 0.0;
	double m_DeltaTime = 0.0;

	__int64 m_BaseTime = 0;
	__int64 m_PausedTime = 0;
	__int64 m_StopTime = 0;
	__int64 m_PrevTime = 0;
	__int64 m_CurrTime = 0;

	bool m_Stopped = false;
};
