/*
 * (1)根据指定学生个数，逐个输入学生信息;
 * (2)逐个显示学生表中所有学生的相关信息;
 * (3)根据姓名进行查找，返回此学生的学号和成绩;
 * (4)根据指定的位置可返回相应的学生信息（学号，姓名，成绩);
 * (5)给定一个学生信息，插入到表中指定的位置;
 * (6)删除指定位置的学生记录;
 * (7)统计表中学生个数。
 */

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#pragma warning(disable : 4996 6031 6054)

//学生数量
int student_count = 0;

typedef struct list {
	int student_number;
	char* student_name;
	int student_score;
	list* next;
};

list* head = nullptr;

//创建链表并录入内容，第一个节点留空,len为长度
void create_list(int len) {
	head = new list;
	list* temp = head;
	for (int i = 0; i < len; ++i) {
		temp->next = new list;
		temp = temp->next;

		int number;
		char* name=new char[13];
		int score;
		printf("【第 %d 个学生】\n", i + 1);
		printf("学号：");
		scanf("%d", &number);
		printf("姓名：");
		scanf("%s", name);
		printf("成绩：");
		scanf("%d", &score);
		
		temp->student_number = number;
		temp->student_name = name;
		temp->student_score = score;
		temp->next = nullptr;
	}
}

//插入一个新节点到链表，index为要插入的位置，范围1至n+1，原节点一律向后移动
//位置为1至n时是一种情况，为n+1时是第二种情况
void list_insert(int index) {
	int number;
	char* name = new char[13];
	int score;
	
	printf("学号：");
	scanf("%d", &number);
	printf("姓名：");
	scanf("%s", name);
	printf("成绩：");
	scanf("%d", &score);

	if (index == student_count + 1) {
		//情况2，直接在最后增加节点
		list* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		list* ready = new list;
		ready->student_number = number;
		ready->student_name = name;
		ready->student_score = score;
		ready->next = nullptr;
		
		temp->next = ready;
	}
	else {
		//情况1，原节点整体后移
		list* before = head;
		for (int i = 0; i < index - 1; ++i) {
			before = before->next;
		}

		list* ready = new list;
		ready->student_number = number;
		ready->student_name = name;
		ready->student_score = score;
		ready->next = before->next;

		before->next = ready;
	}

	++student_count;
}

//删除一个节点，index为要删除的节点的位置
void list_delete(int index) {
	list* before = head;
	for (int i = 0; i < index - 1; ++i) {
		before = before->next;
	}

	list* del = before->next;

	before->next = before->next->next;
	
	delete del;

	--student_count;
}

//(1)根据指定学生个数，逐个输入学生信息
void order1() {
	printf("输入学生个数：");
	int count = 0;
	scanf("%d", &count);

	if (!count) {
		printf("学生数量不能为0");
		return;
	}
	
	student_count = count;
	printf("学生数量：%d\n", count);
	
	create_list(count);
	printf("【√】信息录入完成\n");
}

//(2)逐个显示学生表中所有学生的相关信息
void order2() {
	list* temp = head->next;
	int i = 1;

	while (temp) {
		printf("【学生%d】 学号：%d  姓名：%s  成绩：%d\n",
			i,
			temp->student_number,
			temp->student_name,
			temp->student_score
		);
		
		temp = temp->next;
		++i;
	}

	printf("【√】所有学生信息已显示\n");
}

//(3)根据姓名进行查找，返回此学生的学号和成绩
void order3() {
	char name[13];
	printf("查找姓名：");
	scanf("%s", name);

	list* temp = head->next;

	while (temp) {
		if (!strcmp(name, temp->student_name)) {
			printf("学号：%d  成绩：%d\n",
				temp->student_number,
				temp->student_score
			);

			printf("【√】已找到姓名\n");
			return;
		}
		temp = temp->next;
	}

	printf("【×】未找到姓名\n");
}

//(4)根据指定的位置可返回相应的学生信息（学号，姓名，成绩)
void order4() {
	int index = 0;
	printf("查看位置：");
	scanf("%d", &index);

	if (index > student_count || index < 1) {
		printf("【×】位置 %d 不存在\n", index);
		return;
	}

	list* temp = head;
	for (int i = 0; i < index; ++i) {
		temp = temp->next;
	}
	printf("学号：%d  姓名：%s  成绩：%d\n",
		temp->student_number,
		temp->student_name,
		temp->student_score
	);
	
	printf("【√】位置%d的信息已显示\n", index);
}

//(5)给定一个学生信息，插入到表中指定的位置
//插入位置原有的节点向后移（函数list_insert上有更多注释）
void order5() {
	int index = 0;
	printf("插入位置：");
	scanf("%d", &index);

	if (index > student_count + 1 || index < 1) {
		printf("【×】位置 %d 不存在\n", index);
		return;
	}

	list_insert(index);

	printf("【√】新的信息插入成功\n");
}

//(6)删除指定位置的学生记录
void order6() {
	int index = 0;
	printf("删除位置：");
	scanf("%d", &index);

	if (index > student_count || index < 1) {
		printf("【×】位置 %d 不存在\n", index);
		return;
	}

	list_delete(index);

	printf("【√】位置%d已删除\n", index);
}

//(7)统计表中学生个数
void order7() {
	printf("学生个数：%d\n", student_count);
	printf("【√】统计学生个数成功\n");
}



int main(void) {
	while (1) {
		int input = 0;
		printf("	(1)根据指定学生个数，逐个输入学生信息;\n" \
			   "	(2)逐个显示学生表中所有学生的相关信息;\n" \
			   "	(3)根据姓名进行查找，返回此学生的学号和成绩;\n" \
			   "	(4)根据指定的位置可返回相应的学生信息（学号，姓名，成绩);\n" \
			   "	(5)给定一个学生信息，插入到表中指定的位置;\n" \
			   "	(6)删除指定位置的学生记录;\n" \
			   "	(7)统计表中学生个数。\n");

		printf("请选择：\n");
		scanf("%d", &input);

		if (input != 1 && head == nullptr) {
			printf("【×】没有可用的表，请先使用(1)创建一个新表\n");
			getch();
			continue;
		}

		if (input == 1 && head != nullptr) {
			printf("【×】已有一个表，不可重新创建\n");
			getch();
			continue;
		}

		switch (input) {
			default: {
				printf("输入无效\n");
				getch();
				break;
			}
			case 1: {
				order1();
				getch();
				break;
			}
			case 2: {
				order2();
				getch();
				break;
			}
			case 3: {
				order3();
				getch();
				break;
			}
			case 4: {
				order4();
				getch();
				break;
			}
			case 5: {
				order5();
				getch();
				break;
			}
			case 6: {
				order6();
				getch();
				break;
			}
			case 7: {
				order7();
				getch();
				break;
			}
			
		}


	}
}


