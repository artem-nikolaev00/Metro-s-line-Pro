#include "pch.h"
#include "stdio.h"
#include "../Metro's line/Metro's line.h"
#include "../Metro's line/Metro's line.cpp"

TEST(Constructor, Default) {
	Prog4::Line L;
	Prog4::UStation v1;
	Prog4::Transition v2;
	Prog4::Node v3;
	Prog4::ConstLineIt v4;
}

TEST(Constructor, InitConstructors) {
	std::string s = "abc";

	Prog4::Line L(s);
	ASSERT_EQ("abc", L.nameofline());

	Prog4::UStation v1(s);
	ASSERT_EQ("abc", v1.nameofstation());

	Prog4::Transition v2(s);
	ASSERT_EQ("abc", v2.nameofstation());

	Prog4::Node v3(s);
	ASSERT_EQ("abc", v3.nameofstation());
}

TEST(Metods, parametr1) {
	std::string s = "abc";
	Prog4::UStation* v1 = new Prog4::UStation(s) ;
	Prog4::Line L(s);
	ASSERT_EQ(true, L.empty());
	ASSERT_EQ("abc", L.nameofline());
	Prog4::Item t;
	t.ptr = v1;
	t.tonext = 0;
	t.toprev = 0;
	EXPECT_TRUE(L.newstation(t));
}

TEST(Metods, parametr2) {
	std::string s = "abc";
	std::string sml[3] = { "vvv" };
	std::string smn[3] = { "vvv" };
	Prog4::UStation* v11;
	Prog4::Transition* v22;
	Prog4::Node* v33;

	Prog4::UStation* v1 = new Prog4::UStation(s);
	std::string str1 = v1->typeofstation();
	ASSERT_EQ("Ustation", str1);
	v11 = v1->copy();

	Prog4::Transition* v2 = new Prog4::Transition(s);
	std::string str2 = v2->typeofstation();
	ASSERT_EQ("Transition", str2);
	v22 = v2->copy();
	v2->setlinename(sml, 1);
	for (int i = 0; i < 1; i++) {
		std::string tmp1 = sml[i];
		std::string tmp2 = v2->getlinename(i);
		ASSERT_EQ(tmp1, tmp2);
	}

	Prog4::Node* v3 = new Prog4::Node(s);
	std::string str3 = v3->typeofstation();
	ASSERT_EQ("Node", str3);
	v33 = v3->copy();
	v3->setlinename(sml, smn, 1);
	for (int i = 0; i < 1; i++) {
		std::string tmp1 = sml[i];
		std::string tmp4 = v3->getstationname(i);
		std::string tmp3 = smn[i];
		std::string tmp2 = v3->getlinename(i);
		ASSERT_EQ(tmp1, tmp2);
		ASSERT_EQ(tmp3, tmp4);
	}


}

int tmain() {
	return RUN_ALL_TESTS();
}