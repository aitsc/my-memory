[General]
SyntaxVersion=2
BeginHotkey=81
BeginHotkeyMod=2
PauseHotkey=0
PauseHotkeyMod=0
StopHotkey=69
StopHotkeyMod=2
RunOnce=1
EnableWindow=
MacroID=8ef0a81f-8849-4d4c-a934-0f79f3110f05
Description=远程学习辅助
Enable=1
AutoRun=0
[Repeat]
Type=0
Number=1
[SetupUI]
Type=2
QUI=
[Relative]
SetupOCXFile=
[Comment]
//9.63按键精灵版本
//要求：学习辅助主界面左上角（x67,y83），学习辅助卡片界面左上角（x0,y0），qq对话框左上角（x0,y0），右下角（x1291,y767）
//初始：保证"记住了"按钮是亮的，qq对话框对话部分到最底下
//意外：完全学完检测不到，只测试了win8.1

[Script]
//9.63按键精灵版本
//要求：学习辅助主界面左上角（x67,y83），学习辅助卡片界面左上角（x0,y0），qq对话框左上角（x0,y0），右下角（x1291,y767）
//初始：保证"记住了"按钮是亮的，qq对话框对话部分到最底下
//意外：完全学完检测不到，只测试了win8.1
a = 1
b = 20
c = 10
While (a)
MoveTo 1261, 583//保证鼠标不动

GetColor5 = GetPixelColor(489,538)
GetColor6 = GetPixelColor(481,632)
GetColor9 = GetPixelColor(490,537)
If  GetColor5 <> "FFFFFF" or GetColor6 <> "DED4D6" or GetColor9 <> "FFFFFF" then
	a = 0
	MessageBox "摆放不标准！"
	Goto q1
End If
	
GetColor1 = GetPixelColor(59,597)//记住了
GetColor2 = GetPixelColor(67, 597)//忘记了+下一个
GetColor3 = GetPixelColor(75, 597)//获取答案
GetColor4 = GetPixelColor(82, 597)//获取问题
GetColor10 = GetPixelColor(91, 597)//获取答案加记住了

If     GetColor1 = "000000" and GetColor2 = "FFFFFF" and GetColor3 = "FFFFFF" and GetColor4 = "FFFFFF" Then 
	b=1
ElseIf GetColor1 = "FFFFFF" and GetColor2 = "000000" and GetColor3 = "FFFFFF" and GetColor4 = "FFFFFF" Then 
	b=2
ElseIf GetColor1 = "FFFFFF" and GetColor2 = "FFFFFF" and GetColor3 = "000000" and GetColor4 = "FFFFFF" Then
	b=3
ElseIf GetColor1 = "FFFFFF" and GetColor2 = "FFFFFF" and GetColor3 = "FFFFFF" and GetColor4 = "000000" Then
	b=4
ElseIf GetColor1 = "FFFFFF" and GetColor2 = "FFFFFF" and GetColor3 = "FFFFFF" and GetColor4 = "FFFFFF" and GetColor10 = "000000" Then
	b=5
Else 
	b=6
End If

If b = c Then
	goto q1
Else
c = b
End If

If b = 4 Then 
	MoveTo 225, 154
	Delay 10
	RightClick 1
	MoveTo 331, 291
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 86
	Delay 10
	RightClick 1
	MoveTo 133, 151
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "提问-问题："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1
		
ElseIf b=5 Then
	MoveTo 254, 307
	Delay 10
	LeftClick 3
	MoveTo 227, 400
	Delay 10
	RightClick 1
	MoveTo 315, 540
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 343
	Delay 10
	RightClick 1
	MoveTo 119, 410
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "获取-答案："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1
	Delay 10
	Goto q2
	
ElseIf b = 1 Then
rem q2
	MoveTo 114, 309//准备点击 记住了
	Delay 10
	LeftClick 1
	Delay 400
	IfColor 370, 289, "FFFFFF", 0 Then//准备判断是否结束一组
		MoveTo 227, 330//点击下一组
		Delay 10
		LeftClick 3
		Delay 10
		MoveTo 306, 695//移动到qq输入框
		LeftClick 3
		SayString "结束一轮学习"
		Delay 10
		KeyDown 17, 1//发送
		KeyPress 13, 1
		KeyUp 17, 1
		goto q1
	End If
	IfColor 193, 293, "FFFFFF", 0 Then//准备是否复习完成
		MoveTo 273, 329//点击确定
		Delay 10
		LeftClick 3
		Delay 100
		MoveTo 140, 420//点击学习
		Delay 10
		LeftClick 2
		Delay 10
		MoveTo 648, 115//拖动学习栏
		LeftDown 1
		Delay 10
		MoveTo 0,0
		Delay 10
		LeftUp 1
		Delay 10
		MoveTo 306, 695//移动到qq输入框
		LeftClick 3
		SayString "复习完成"
		Delay 10
		KeyDown 17, 1//发送
		KeyPress 13, 1
		KeyUp 17, 1
		goto q1
	End If
	MoveTo 225, 154//右键菜单
	Delay 10
	RightClick 1
	MoveTo 331, 291//移动到全选处
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 86//右键菜单
	Delay 10
	RightClick 1
	MoveTo 133, 151//移动到复制处
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "记住了-问题："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1

ElseIf b = 2 Then
	MoveTo 394, 309
	Delay 10
	LeftClick 3
	MoveTo 227, 400
	Delay 10
	RightClick 1
	MoveTo 315, 540
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 343
	Delay 10
	RightClick 1
	MoveTo 119, 410
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "忘记了-答案："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1
	
	Delay 10
	MoveTo 254, 307
	Delay 10
	LeftClick 1
	MoveTo 225, 154
	Delay 10
	RightClick 1
	MoveTo 331, 291
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 86
	Delay 10
	RightClick 1
	MoveTo 133, 151
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "下一个-问题："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1
	
ElseIf b=3 Then
	MoveTo 254, 307
	Delay 10
	LeftClick 3
	MoveTo 227, 400
	Delay 10
	RightClick 1
	MoveTo 315, 540
	Delay 10
	LeftClick 1//全选
	MoveTo 30, 343
	Delay 10
	RightClick 1
	MoveTo 119, 410
	Delay 10
	LeftClick 1//复制
	MoveTo 306, 695
	Delay 10
	LeftClick 3
	SayString "获取-答案："
	KeyPress "Enter", 1
	KeyDown 17, 1
	KeyPress 86, 1
	KeyUp 17, 1
	Delay 10
	KeyDown 17, 1//发送
	KeyPress 13, 1
	KeyUp 17, 1
	
Else 
End If

rem q1
Delay 10
Wend
