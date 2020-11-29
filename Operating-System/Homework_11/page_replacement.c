#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define FRAME_NUMBERS 1
#define FIFO 2
#define LRU 3
#define OPTIMAL 4
#define EXIT 5
#define SEED 6
#define PAGE_REFERENCE_NUM 32
int count_frame;
int page_ref[PAGE_REFERENCE_NUM];
int p[7];
int count_fault = 0;

void getData()
{
	srand(SEED);
	for (int i = 0; i < PAGE_REFERENCE_NUM; i++) {
		page_ref[i] = rand() % 10;
	}
	printf("\nEnter the number of frames(2~7) : ");
	scanf("%d", &count_frame);
}

void initialize()
{
	count_fault = 0;  //전역변수 초기화
	for (int i = 0; i < count_frame; i++)
		p[i] = 9999;   //프레임 초기화
	printf("page reference string :");  // print page reference string
	for (int i = 0; i < PAGE_REFERENCE_NUM; i++) {
		printf(" %d", page_ref[i]);
	}
	printf("\n");
}

int isHit(int data)   // data가 p배열에 있으면 hit !
{
	int hit = FALSE;
	for (int j = 0; j < count_frame; j++)
	{
		if (p[j] == data)
		{
			hit = TRUE;
			break;
		}

	}
	return hit;
}


void print_frames()  //현재까지의 page frame 정보를 출력
{
	for (int k = 0; k < count_frame; k++)
	{
		if (p[k] != 9999)
			printf(" %d", p[k]);
	}
}

void print_page_faults()  //전체 page fault 갯수를 출력
{
	printf("\nTotal the number of page faults:%d\n\n", count_fault);
}

void fifo()
{
	initialize();
	int k;
	for (int i = 0; i < PAGE_REFERENCE_NUM; i++)
	{
		printf("\nFor %d :", page_ref[i]);

		if (isHit(page_ref[i]) == FALSE) //page replacement 발생
		{
			for (k = 0; k < count_frame - 1; k++)
				p[k] = p[k + 1]; // 한칸씩 옮기기

			p[k] = page_ref[i];  //배열의 마지막 위치에 값 대입
			count_fault++;
			print_frames();
		}
		else
			printf(" No page fault");
	}
	print_page_faults();
}


void optimal()
{
	initialize();
	int near[7];
	int flag = FALSE;
	for (int i = 0; i < PAGE_REFERENCE_NUM; i++)
	{
		flag = FALSE;
		printf("\nFor %d :", page_ref[i]);

		if (isHit(page_ref[i]) == FALSE)//page replacement 발생
		{
			
			for (int j = 0; j < count_frame; j++)
			{
				int pg = p[j];
				int found = FALSE;
				for (int k = i; k < PAGE_REFERENCE_NUM; k++)
				{
					if (pg == page_ref[k])
					{
						near[j] = k;
						found = TRUE;
						break;
					}
					else
						found = FALSE;
				}
				if (!found)
					near[j] = 9999;
			}
			int max = -9999;
			int replace_index;
			for (int j = 0; j < count_frame; j++)
			{
				for (int n = 0; n < count_frame; n++) {
					if (p[n] == 9999) {
						p[n] = page_ref[i];
						flag = TRUE;
						break;
					}
				}
				if (flag == TRUE) {
					break;
				}
				if (near[j] > max)
				{
					max = near[j];
					replace_index = j;
				}
			}
			if (flag == FALSE) {
				p[replace_index] = page_ref[i];
			}
			count_fault++;
			print_frames();
		}
		else
			printf(" No page fault");
	}
	print_page_faults();
}

void lru()
{
	initialize();
	int least[50];
	for (int i = 0; i < PAGE_REFERENCE_NUM; i++)
	{
		printf("\nFor %d :", page_ref[i]);

		if (isHit(page_ref[i]) == FALSE)//page replacement 발생
		{
			for (int j = 0; j < count_frame; j++)
			{
				int pg = p[j];
				int found = FALSE;
				for (int k = i - 1; k >= 0; k--)
				{
					if (pg == page_ref[k])
					{
						least[j] = k;
						found = TRUE;
						break;
					}
					else
						found = FALSE;
				}
				if (!found)
					least[j] = -9999;
			}
			int min = 9999;
			int replace_index;
			for (int j = 0; j < count_frame; j++)
			{
				if (least[j] < min)
				{
					min = least[j];
					replace_index = j;
				}
			}
			p[replace_index] = page_ref[i];
			count_fault++;
			print_frames();
		}
		else
			printf(" No page fault");
	}
	print_page_faults();
}


int main()
{
	int choice;
	do {
		printf("Page Replacement Algorithm\n1.Enter the Data\n2.FIFO\n3.LRU\n4.Optimal\n5.Exit\nEnter your choice: ");
		scanf("%d", &choice);
		if (choice == FRAME_NUMBERS) {
			getData();
		}
		else if (choice == FIFO) {
			fifo();
		}
		else if (choice == LRU) {
			lru();
		}
		else if (choice == OPTIMAL) {
			optimal();
		}
		else if (choice == EXIT) {
			break;
		}
		else {
			continue;
		}
	} while (TRUE);

	return 0;
}