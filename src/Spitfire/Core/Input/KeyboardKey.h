#pragma once

// GLFW Base code

namespace Spitfire {

	enum class KeyboardKey : int {
		Space = 32,
		Apostrophe = 39,	//  ' 
		Comma = 44,			//  ,
		Minus = 45,			//  -
		Period = 46,		//  .
		Slash = 47,			//  /
		
		D0 = 48,			//  0
		D1 = 49,			//  1
		D2 = 50,			//  2
		D3 = 51,			//  3
		D4 = 52,			//  4
		D5 = 53,			//  5
		D6 = 54,			//  6
		D7 = 55,			//  7
		D8 = 56,			//  8
		D9 = 57,			//  9

		Semicolon = 59,		//  ;
		Equal = 61,			//  =

		A = 65,				//  A
		B = 66,				//  B
		C = 67,				//  C
		D = 68,				//  D
		E = 69,				//  E
		F = 70,				//  F
		G = 71,				//  G
		H = 72,				//  H
		I = 73,				//  I
		J = 74,				//  J
		K = 75,				//  K
		L = 76,				//  L
		M = 77,				//  M
		N = 78,				//  N
		O = 79,				//  O
		P = 80,				//  P
		Q = 81,				//  Q
		R = 82,				//  R
		S = 83,				//  S
		T = 84,				//  T
		U = 85,				//  U
		V = 86,				//  V
		W = 87,				//  W
		X = 88,				//  X
		Y = 89,				//  Y
		Z = 90,				//  Z

		LeftBracket = 91,	//  [
		Backslash = 92,		//  \ 
		RightBracket = 93,	//  ]
		GraveAccent = 96,	//  `
		
		World1 = 161,		//  non-US #1
		World2 = 162,		//  non-US #2

		Escape = 256,		//  Escape
		Enter = 257,		//  Enter
		Tab = 258,			//  Tab
		Backspace = 259,	//  Backspace
		Insert = 260,		//  Insert
		Delete = 261,		//  Delete

		Right = 262,		//  Arrow-Right
		Left = 263,			//  Arrow-Left
		Down = 264,			//  Arrow-Down
		Up = 265,			//  Arrow-Up

		PageUp = 266,		//  Page-Up
		PageDown = 267,		//	Page-Down
		Home = 268,			//  Home
		End = 269,			//  End
		CapsLock = 280,		//  CapsLock
		ScrollLock = 281,	//  ScrollLock
		NumLock = 282,		//  NumLock
		PrintScreen = 283,	//  PrintScreen
		Pause = 284,		//  Pause

		F1 = 290,			//  F1
		F2 = 291,			//  F2
		F3 = 292,			//  F3
		F4 = 293,			//  F4
		F5 = 294,			//  F5
		F6 = 295,			//  F6
		F7 = 296,			//  F7
		F8 = 297,			//  F8
		F9 = 298,			//  F9
		F10 = 299,			//  F10
		F11 = 300,			//  F11
		F12 = 301,			//  F12
		F13 = 302,			//  F13
		F14 = 303,			//  F14
		F15 = 304,			//  F15
		F16 = 305,			//  F16
		F17 = 306,			//  F17
		F18 = 307,			//  F18
		F19 = 308,			//  F19
		F20 = 309,			//  F20
		F21 = 310,			//  F21
		F22 = 311,			//  F22
		F23 = 312,			//  F23
		F24 = 313,			//  F24
		F25 = 314,			//  F25
		Kp0 = 320,			//  Kp0
		Kp1 = 321,			//  Kp1
		Kp2 = 322,			//  Kp2
		Kp3 = 323,			//  Kp3
		Kp4 = 324,			//  Kp4
		Kp5 = 325,			//  Kp5
		Kp6 = 326,			//  Kp6
		Kp7 = 327,			//  Kp7
		Kp8 = 328,			//  Kp8
		Kp9 = 329,			//  Kp9

		KpDecimal = 330,	//  Keypad-Decimal
		KpDivide = 331,		//  Keypad-Divide
		KpMultiply = 332,	//  Keypad-Multiply
		KpSubtract = 333,	//  keypad-Subtract
		KpAdd = 334,		//  keypad-Add
		KpEnter = 335,		//  keypad-Enter
		KpEqual = 336,		//  keypad-Equal
		LeftShift = 340,	//	LeftShift
		LeftControl = 341,	//  LeftControl
		LeftAlt = 342,		//  LeftAlt
		LeftSuper = 343,	//  LeftSuper
		RightShift = 344,	//  RightShift
		RightControl = 345,	//  RightControl
		RightAlt = 346,		//  RightAlt
		RightSuper = 347,	//  RightSuper
		Menu = 348			//  Menu
	};
}