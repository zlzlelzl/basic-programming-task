#include <stdio.h>
#include <windows.h> // Sleep, exit(0) 과 system("cls") 를 사용하기 위한 헤더파일
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 25
struct menu{
	int type;//헤더노드의 타입은 목표치
	int count;
	int price;
	int stock;
	char *name;
	struct menu *link;//전체메뉴 리스트
	struct menu *rlink;//현재고객이 시키고 있는 메뉴 리스트
}*lastAll,*lastNow, *startQueue, *lastQueue;
int QueueCount=0;
struct card{
	char *name;
	int type;//헤더노드에서는 카드의 수량
	int ratio;
	struct card * link;
}*lastCard;
//커서를 x,y,좌표로 옮긴다.
void gotoxy(int x,int y){
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
void saveData_menu(struct menu *start){
	FILE *a=fopen("product.txt","w");//쓰기모드로 연다.
	int j;
	struct menu *temp;
	temp = start;

	fprintf(a,"%d\n",temp->count);//헤더노드의 상품갯수를 저장.

	for(j=0;j<start->count+1;j++){//헤더노드의 다른정보들까지 저장한다.
		fprintf(a,"%d %d %d %d %s\n",temp->type,temp->count,temp->price,temp->stock,temp->name);
		temp=temp->link;
	}
	fclose(a);
}
void saveData_menu_eod(struct menu *start){//다음날 영업을 위해 금일에 대한 정보를 지운다.
	struct menu *temp;
	temp = start;
	temp->price=0;//일일판매량 초기화
	temp->stock=0;//현재 고객의 합계 초기화
	temp = start->link;
	while(temp){
		temp->count=0;
		temp = temp->link;
	}
	saveData_menu(start);
}
void saveData_card(struct card *startCard){
	FILE *b=fopen("card.txt","w");//쓰기모드로 연다.
	int j;
	struct card *tempCard;
	tempCard = startCard;

	fprintf(b,"%d\n",tempCard->type);//헤더노드의 카드갯수를 저장.

	for(j=0;j<startCard->type+1;j++){//헤더노드의 다른정보들까지 저장한다.
		fprintf(b,"%d %d %s\n",tempCard->type,tempCard->ratio,tempCard->name);
		tempCard=tempCard->link;
	}
	fclose(b);
}
//보여주는 화면과 버튼 화면 분리
void drawmain(){
	int i;
	for(i=0;i<40;i++){
		gotoxy(90,i); printf("│");
	}
	//첫째줄
	gotoxy(92,0);
	printf("┌──────┐\n");
	gotoxy(92,1);
	printf("│⑦  Sells   │\n");
	gotoxy(92,2);
	printf("│            │\n");
	gotoxy(92,3);
	printf("│    판매    │\n");
	gotoxy(92,4);
	printf("└──────┘\n");
	gotoxy(108,0);
	printf("┌──────┐\n");
	gotoxy(108,1);
	printf("│⑧ Historys │\n");
	gotoxy(108,2);
	printf("│            │\n");
	gotoxy(108,3);
	printf("│거래내역조회│\n");
	gotoxy(108,4);
	printf("└──────┘\n");
	//둘째줄
	gotoxy(92,5);
	printf("┌──────┐\n");
	gotoxy(92,6);
	printf("│④  Stocks  │\n");
	gotoxy(92,7);
	printf("│            │\n");
	gotoxy(92,8);
	printf("│ 재고량조회 │\n");
	gotoxy(92,9);
	printf("└──────┘\n");
	gotoxy(108,5);
	printf("┌──────┐\n");
	gotoxy(108,6);
	printf("│⑤  Goals   │\n");
	gotoxy(108,7);
	printf("│            │\n");
	gotoxy(108,8);
	printf("│ 목표치분석 │\n");
	gotoxy(108,9);
	printf("└──────┘\n");
	//셋째줄
	gotoxy(92,10);
	printf("┌──────┐\n");
	gotoxy(92,11);
	printf("│① Products │\n");
	gotoxy(92,12);
	printf("│            │\n");
	gotoxy(92,13);
	printf("│  상품등록  │\n");
	gotoxy(92,14);
	printf("└──────┘\n");
	gotoxy(108,10);
	printf("┌──────┐\n");
	gotoxy(108,11);
	printf("│②  Cards   │\n");
	gotoxy(108,12);
	printf("│            │\n");
	gotoxy(108,13);
	printf("│할인카드등록│\n");
	gotoxy(108,14);
	printf("└──────┘\n");
	//넷째줄
	gotoxy(92,15);
	printf("┌──────┐\n");
	gotoxy(92,16);
	printf("│ⓞ  E.O.D   │\n");
	gotoxy(92,17);
	printf("│            │\n");
	gotoxy(92,18);
	printf("│  영업마감  │\n");
	gotoxy(92,19);
	printf("└──────┘\n");
	gotoxy(108,15);
	printf("┌──────┐\n");
	gotoxy(108,16);
	printf("│③  Editor  │\n");
	gotoxy(108,17);
	printf("│            │\n");
	gotoxy(108,18);
	printf("│ 만든사람들 │\n");
	gotoxy(108,19);
	printf("└──────┘\n");
}
struct card* searchCard(int type,struct card *startCard){//같은 메뉴가 전체리스트에 있는지 없는지 검사
	struct card *temp=NULL;
	temp=startCard->link;//첫노드는 헤더노드라서 빼고
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
void attach_card(int type,int ratio,struct card *startCard){//리스트뒤에 노드 붙이기(전체리스트)
	struct card *temp=NULL;
	//전체리스트 검색 후 노드 할당및 수량 증가
	temp=searchCard(type,startCard);
	if(temp != NULL){
		temp->ratio = ratio;
	}else{
		startCard->type++;
		temp=(struct card*)malloc(sizeof(*temp));
		temp->type=type;
		lastCard->link=temp;
		lastCard=temp;
		lastCard->link=NULL;
	}
	
}
struct menu* searchAll(int type,struct menu *start){//같은 메뉴가 전체리스트에 있는지 없는지 검사
	struct menu *temp=NULL;
	temp=start->link;//첫노드는 헤더노드라서 빼고
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
struct menu* searchNow(int type,struct menu *start){//같은 메뉴가 현재고객리스트에 있는지 없는지 검사
	struct menu *temp=NULL;
	temp=start->rlink;//첫노드는 헤더노드라서 빼고
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->rlink;
	}
	return temp;
}
void attach(int type,int num,struct menu *start){//리스트뒤에 노드 붙이기(전체리스트)
	struct menu *temp=NULL,*temp1=NULL;
	//전체리스트 검색 후 노드 할당및 수량 증가
	temp=searchAll(type,start);
	if(temp != NULL){
		temp->count=temp->count+num;
		temp->stock = temp->stock - num;
	}else{
		start->count++;
		temp=(struct menu*)malloc(sizeof(*temp));
		temp->type=type;
		temp->count=num;
		temp->stock =temp->stock -num;
		lastAll->link=temp;
		lastAll=temp;
		lastAll->link=NULL;
	}

	//현재 고객의 메뉴 리스트(오른쪽 하단에 출력하기 위함)
	temp1=searchNow(type,start);
	if(temp1 != NULL){
		temp1->count=temp1->count+num;
	}else{
		temp1=(struct menu*)malloc(sizeof(*temp1));
		temp1->type=type;
		temp1->count=num;
		temp1->name = temp->name;
		temp1->price = temp->price;
		temp1->stock = 100;
		lastNow->rlink=temp1;
		lastNow=temp1;
		lastNow->rlink=NULL;
	}
	
	
}
void attach_Queue(int type,int num,struct menu *start,int discount){
	struct menu *temp=NULL,*temp1=NULL;
	QueueCount++;
	if(QueueCount > 25){
		temp = startQueue;
		startQueue= startQueue->link;
		free(temp);
	}
	temp1 = searchNow(type,start);
	temp=(struct menu*)malloc(sizeof(*temp));
	temp->type=type;
	temp->count=num;
	temp->name = temp1->name;
	temp->price = temp1->price * num;
	temp->stock = discount;
	lastQueue->link = temp;
	lastQueue=temp;
	lastQueue->link=NULL;
}
void drawsells(struct menu *start,struct card *startCard){//주문화면 그리기
	struct menu *temp;
	struct card *tempCard;
	int count = start->count;
	int countHalf,i;
	temp=start->link;
	countHalf = count/2 + count%2;//짝수일땐 절반 홀수일땐 1개 많은 메뉴를 앞에 출력한다.

	tempCard = startCard->link;


	gotoxy(3,3);
	printf("      메뉴                   가격               메뉴                    가격");
	gotoxy(3,4);
	printf("──────────────────────────────────────────");
	for(i=0;i<countHalf;i++){
		gotoxy(4,6+i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(32,6+i);
		printf("%d",temp->price);
		temp = temp->link;
	}
	for(i=0;i<count-countHalf;i++){
		gotoxy(45,6+i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(75,6+i);
		printf("%d",temp->price);
		temp = temp->link;
	}
	gotoxy(4,6+countHalf+2);
	printf("할인카드");
	for(i=0;i<startCard->type;i++){
		gotoxy(4,6+countHalf+3+i);
		printf("%d.%s",tempCard->type,tempCard->name);
		gotoxy(25,6+countHalf+3+i);
		printf("%d%%",tempCard->ratio);
		tempCard = tempCard->link;
	}
}
void sells(struct menu *start,struct card *startCard){
	int type=0,num,i=0,sum=0,discount=0,tempsum=0;
	struct menu *temp,*deletetemp,*deletetempstart;
	struct card *tempCard;
	while(1){
		saveData_menu(start);
		temp=start;
		system("cls");
		
		drawmain();//전체모양 그리기
		drawsells(start,startCard);//안쪽에 메뉴 그리기
		gotoxy(3,34);
		printf("메뉴 입력 (메뉴 수량):");
		if(type>=31 && type<=(startCard->type+30)){
			tempCard = searchCard(type,startCard);
			discount = tempCard->ratio;
		}
		//if(type>21){//범위를 초과한 입력
		//	gotoxy(35,34);
		//	printf("잘못된 입력입니다.");
		//}
		if(type>=1 && type<=start->count || type>=31 && type<=(startCard->type+30)){//1번~20번 사이의 메뉴를 입력시 오른쪽 아래화면에 총액수및 주문시킨 현황을 보여줌/할인카드 입력시 할인된 금액까지해서 화면에 다시 뿌려줌.
			temp=temp->rlink;//초기노드는 헤더노드 따라서 두번째 노드부터 시작.
			i=0;
			sum=0;
			while(temp){
				sum=sum + temp->price*temp->count;//총액 계산
				if(temp->count != 0){//중도 취소되어 수량이 0이 될경우 출력하지 않는다.
					gotoxy(92,25+i);//오른쪽 아래 위치
					printf("%d.%s",temp->type,temp->name);
					gotoxy(115,25+i);//오른쪽 아래 위치
					printf("%d개",temp->count);
					i++;
				}
				temp=temp->rlink;
			}
			tempsum = sum;
			tempsum = tempsum*discount/100;
			
			gotoxy(92,35);
			printf("────────────────");
			gotoxy(92,36);
			printf("합계 : %d - %d = %d",sum,tempsum,sum - tempsum);
			
		}
		if(type>=1 && type<=start->count){//현재까지 팔린 총 액수 계산
			temp=start->link;//초기노드는 헤더노드 따라서 두번째 노드부터 시작.
			start->price=0;
			while(temp){
				start->price=start->price + temp->price*temp->count;//헤더노드에 총 액수 저장
				temp=temp->link;
			}
		}
		gotoxy(3,35);
		printf("───────────────────────────────────────────");
		gotoxy(3,36);
		printf("0 : 상위메뉴 이동 / 50 : 결제 / 제품의 고유번호로 주문 /중간취소시 갯수에 -붙여 주문");
		gotoxy(25,34);
		scanf("%d",&type);
		if(type>=1 && type<=start->count){//1번~20번 사이의 메뉴만 구조체 리스트에 포함시킨다.
			scanf("%d",&num);
			if(num != 0){//수량이 0이 아니면//0이면 리스트에 추가 안함.
				attach(type,num,start);
				attach_Queue(type,num,start,10);
			}
			
		}else if(type == 50){
			discount = 0;
			deletetempstart=start->rlink;//첫노드를 제외하고 모두 메모리해제
			while(deletetempstart){
				deletetemp = deletetempstart;
				deletetempstart=deletetempstart->rlink;
				free(deletetemp);
				
			}
			start->rlink = NULL;
			lastNow=start;
		}else if(type==0){
			break;
		}
		

	}

}
void drawstocks(struct menu *start){
	struct menu *temp;
	int i=4,j,bestnum=0,bestindex=0;
	temp = start;
	temp=temp->link;
	gotoxy(1,1);
	printf("────────────────────────────────────────────");
	gotoxy(1,2);
	printf("   제품명                      재고량                    판매량              비고");
	gotoxy(1,3);
	printf("────────────────────────────────────────────");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(25,i);
		for(j=0;j<temp->stock/10;j++){
			printf("■");
			if(j==9){//최대 10개까지만 그림.
				break;
			}
		}
		printf("%d",temp->stock);
		gotoxy(60,i);
		printf("%d",temp->count);
		if(temp->count>bestnum){
			bestnum = temp->count;
			bestindex=i;
		}
		i++;
		temp=temp->link;
		
	}
	if(bestnum != 0){
		gotoxy(75,bestindex);
		printf("★인기제품★");
	}
	
	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동 / 재고량 추가시 제품고유번호 입력 후 수량 입력\n");
}
void stocks(struct menu *start){
	struct menu *temp1;
	int type,num;
	
	while(1){
		saveData_menu(start);//내용수정된거 저장
		system("cls");
		drawmain();
		drawstocks(start);
		gotoxy(1,34);
		printf("재고량 수정(메뉴 추가할수량):");
		scanf("%d",&type);
		if(type == 0){
			break;
		}else{
			scanf("%d",&num);
			temp1=searchAll(type,start);
			temp1->stock = temp1->stock + num;
		}
	}
	

}
void drawgoals(struct menu *start){
	float goal=((float)start->price/start->type)*100;//int형이기때문에 형변환이 필요함.
	int i;
	gotoxy(1,2);
	printf("────────────────────────────────────────────");
	gotoxy(1,3);
	printf("   목표액                      판매액                목표금액 - 판매금액              ");
	gotoxy(1,4);
	printf("────────────────────────────────────────────");

	gotoxy(3,5);
	printf("%d",start->type);
	gotoxy(32,5);
	printf("%d",start->price);
	gotoxy(60,5);
	printf("%d",start->type-start->price);



		gotoxy(18,15);
	printf("┌─────────────────┐");
	gotoxy(18,16);
	printf("│목표게이지                        │");

	gotoxy(18,17);
	printf("│");
	gotoxy(26,17);
		for(i=0;i<goal/10;i++){
			printf("■");
			if(i==9){//최대 10개까지만 그림.
				break;
			}
	}
	gotoxy(54,17);
	printf("│");
	gotoxy(18,18);
	printf("│                          %.1f%%",goal);
	gotoxy(54,18);
	printf("│");
	gotoxy(18,19);
	printf("└─────────────────┘");




	gotoxy(1,34);
	printf("메뉴입력 : ");
	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동/ 1 : 목표액 변경");
	
}
void goals(struct menu *start){
	int exit=0,type;//type이 목표치
	while(1){
		saveData_menu(start);//내용수정된거 저장
		system("cls");
		drawmain();//전체모양 그리기
		drawgoals(start);
		gotoxy(12,34);
		scanf("%d",&exit);
		if(exit == 0){
			break;
		}else if(exit == 1){
			scanf("%d",&type);
			start->type = type;
		}
	}
	


}
void draweod(struct menu *start){//모든자료 출력
	struct menu *temp;
	int i=4;
	temp = start->link;
	gotoxy(1,1);
	printf("────────────────────────────────────────────");
	gotoxy(1,2);
	printf("   제품명               판매수량               판매액               재고량");
	gotoxy(1,3);
	printf("────────────────────────────────────────────");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(28,i);
		printf("%d",temp->count);
		gotoxy(48,i);
		printf("%d",temp->count*temp->price);
		gotoxy(70,i);
		printf("%d",temp->stock);
		temp=temp->link;
		i++;
	}
	gotoxy(1,i);
	printf("────────────────────────────────────────────");
	gotoxy(1,++i);
	printf("총 매출 : %d",start->price);
	gotoxy(1,++i);
	printf("목표금액 : %d",start->type);
	gotoxy(1,++i);
	printf("달성률 : %d%%",start->price / start->type * 100);
	gotoxy(1,34);
	printf("메뉴입력 : ");
	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동/ 100 : 영업마감(마감시 모든 정보가 초기화 됩니다)");
	

	

}
void eod(struct menu *start){
	int exit=1;//0도 100도 아닌값을 설정->마감시에만 정보를 출력하기 때문
	while(1){
		system("cls");
		drawmain();
		if(exit == 0){
				break;
		}else if(exit == 100){
			draweod(start);
			saveData_menu_eod(start);
		}
		gotoxy(1,34);
		printf("메뉴입력 : ");
		gotoxy(1,35);
		printf("────────────────────────────────────────────");
		gotoxy(1,36);
		printf("0 : 상위메뉴 이동/ 100 : 영업마감(마감시 모든 정보가 초기화 됩니다)");
		gotoxy(12,34);
		scanf("%d",&exit);
		
		
	}
}
struct menu* MemoryAllocation(){
	struct menu *temp;
	temp=(struct menu*)malloc(sizeof(*temp));
	temp->name = (char*)malloc(sizeof(char[15]));
	temp->rlink=NULL;
	temp->link=NULL;
	return temp;
}
struct card * MemoryAllocation_card(){
	struct card *temp;
	temp=(struct card *)malloc(sizeof(*temp));
	temp->name = (char*)malloc(sizeof(char[15]));
	temp->link=NULL;
	return temp;
}
void drawCards(struct card *startCard){
	struct card *temp;
	int i=4;
	temp = startCard->link;
	gotoxy(1,1);
	printf("────────────────────────────────────────────");
	gotoxy(1,2);
	printf("   카드명                      할인율                                 ");
	gotoxy(1,3);
	printf("────────────────────────────────────────────");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(34,i);
		printf("%d%%",temp->ratio);

	
		temp=temp->link;
		i++;
	}
	gotoxy(1,34);
	printf("메뉴입력 : ");
	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동/ 1 : 카드 등록 / 2 : 카드 수정 / 3 : 카드 삭제");
}
void cards(struct card *startCard){
	int exit,i,cnt;
	int ratio;
	int type;
	char name[15];
	struct card *temp ,*deletetemp;
	while(1){
		saveData_card(startCard);//모든 카드정보 수정하여 계속 저장.
		system("cls");
		drawmain();
		drawCards(startCard);
		gotoxy(12,34);
		scanf("%d",&exit);
		if(exit==0){
			break;
		}else if(exit == 1){//카드등록
			gotoxy(1,31);
			printf("카드명 입력:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("할인율 입력:");
			scanf("%d",&ratio);

			temp = MemoryAllocation_card();
			strcpy(temp->name,name);
			//temp->name = name;
			temp->ratio = ratio;
			temp->type = ++startCard->type+30;//총 카드수의 1을 더해 타입을 지정하고 총 메뉴수 또한 증가시킨다.
			lastCard->link = temp;
			lastCard = temp;
			lastCard->link=NULL;
		}else if(exit == 2){//카드수정
			gotoxy(1,31);
			printf("카드고유번호 입력:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){
				gotoxy(1,32);
				printf("카드명 입력:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("할인율 입력:");
				scanf("%d",&ratio);
				strcpy(temp->name,name);
				temp->ratio = ratio;
			}
		}else if(exit == 3){//카드삭제
			gotoxy(1,31);
			printf("카드고유번호 입력:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){//타입이 같은 노드가 있다면
				deletetemp = startCard;//다음노드부터 살펴봐야되므로 start부터 시작
				cnt=startCard->type;//현재의 갯수를 cnt에 저장
				startCard->type--;//삭제되니까 1감소
				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//다음노드가 temp와 같다면 그 노드의 링크를 temp의 링크가 가리키는 곳을 가리키게 한다.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//맨뒤의 노드가 삭제됐다면 마지막노드를 가리키는 포인터를 옮겨줘야함.
							lastCard=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//type을 다시 설정
				deletetemp=startCard->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i+30;//type을 다시 설정
					i++;
					deletetemp=deletetemp->link;
				}
			
			}
		}else{
		
		}
	}
}

void drawHistorys(){
	struct menu *temp;
	int i=4;
	temp = startQueue->link;
	gotoxy(1,1);
	printf("────────────────────────────────────────────");
	gotoxy(1,2);
	printf("   제품명                      수  량                    판매액             할인카드");
	gotoxy(1,3);
	printf("────────────────────────────────────────────");
	if(temp == NULL){
		gotoxy(1,i);
		printf("최근 거래 내역이 없습니다.");
	}
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(34,i);
		printf("%d",temp->count);
		gotoxy(59,i);
		printf("%d",temp->price);
	
		temp=temp->link;
		i++;
	}

	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동\n");
}
void historys(){
	int exit;
	while(1){
		system("cls");
		drawmain();
		drawHistorys();
		gotoxy(1,34);
		scanf("%d",&exit);
		if(exit==0){
			break;
		}
	}
}


void drawproducts(struct menu *start){
	struct menu *temp;
	int i=4;
	temp = start->link;
	gotoxy(1,1);
	printf("────────────────────────────────────────────");
	gotoxy(1,2);
	printf("   제품명                      판매액                    재고량             ");
	gotoxy(1,3);
	printf("────────────────────────────────────────────");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(34,i);
		printf("%d",temp->price);
		gotoxy(59,i);
		printf("%d",temp->stock);
	
		temp=temp->link;
		i++;
	}
	gotoxy(1,34);
	printf("메뉴입력 : ");
	gotoxy(1,35);
	printf("────────────────────────────────────────────");
	gotoxy(1,36);
	printf("0 : 상위메뉴 이동/ 1 : 제품 등록 / 2 : 제품 수정 / 3 : 제품 삭제");
}

void products(struct menu *start){
	int exit,i,cnt;
	int price;
	int stock;
	int type;
	char name[15];
	struct menu *temp ,*deletetemp;
	while(1){
		system("cls");
		drawmain();
		drawproducts(start);
		gotoxy(12,34);
		scanf("%d",&exit);
		if(exit==0){
			break;
		}else if(exit == 1){//제품등록
			gotoxy(1,31);
			printf("제품명 입력:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("가격 입력:");
			scanf("%d",&price);
			gotoxy(1,33);
			printf("재고량 입력:");
			scanf("%d",&stock);
			temp = MemoryAllocation();
			strcpy(temp->name,name);
			temp->price = price;
			temp->stock = stock;
			temp->type = ++start->count;//총 메뉴수의 1을 더해 타입을 지정하고 총 메뉴수 또한 증가시킨다.
			temp->count=0;
			lastAll->link = temp;
			lastAll = temp;
			lastAll->link=NULL;
		}else if(exit == 2){//제품수정
			gotoxy(1,31);
			printf("제품고유번호 입력:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){
				gotoxy(1,32);
				printf("제품명 입력:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("가격 입력:");
				scanf("%d",&price);
				temp->name = name;
				temp->price = price;
			}
		}else if(exit == 3){//제품삭제
			gotoxy(1,31);
			printf("제품고유번호 입력:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){//타입이 같은 노드가 있다면
				deletetemp = start;//다음노드부터 살펴봐야되므로 start부터 시작
				cnt=start->count;//현재의 갯수를 cnt에 저장
				start->count--;

				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//다음노드가 temp와 같다면 그 노드의 링크를 temp의 링크가 가리키는 곳을 가리키게 한다.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//맨뒤의 노드가 삭제됐다면 마지막노드를 가리키는 포인터를 옮겨줘야함.
							lastAll=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//타입을 다시 설정하는 부분. 중간에 삭제될 경우/
				deletetemp=start->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i;//type을 다시 설정
					i++;
					deletetemp=deletetemp->link;
				}
				
			}
		}else{
		
		}
	}
}

void loadDataAll(struct menu **start,struct card **startCard){
	int j,cnt=0;
	struct menu *temp=NULL;
	struct card *tempCard=NULL;
	FILE *a=fopen("product.txt","a");//파일이 없는경우는 빈파일을 만들어주고 있는경우는 그냥 열었다가 닫는다.
	FILE *b=fopen("card.txt","a");
	fclose(a);//읽기모드를 열기위해 실행시킨다.
	fclose(b);

	a=fopen("product.txt","r");//읽기모드로 연다. 이렇게 해줌으로써 파일포인터가 맨앞에 위치.

	*start = MemoryAllocation();
	lastAll=*start;
	lastNow=*start;
	
	fscanf(a,"%d",&cnt);

	//헤더노드 저장
	fscanf(a,"%d %d %d %d",&(*start)->type,&(*start)->count,&(*start)->price,&(*start)->stock);
	fscanf(a,"%s\n",(*start)->name);
	//============


	for(j=0;j<cnt;j++){
		temp = MemoryAllocation();
		lastAll->link = temp;
		fscanf(a,"%d %d %d %d",&temp->type,&temp->count,&temp->price,&temp->stock);
		fscanf(a,"%s\n",temp->name);
		lastAll = lastAll->link;
	}
	fclose(a);//제품정보 읽어보기


	b=fopen("card.txt","r");//읽기모드로 연다. 카드정보 읽어보기시작
	*startCard = MemoryAllocation_card();
	lastCard=*startCard;

	fscanf(a,"%d",&cnt);

	//헤더노드 저장
	fscanf(a,"%d %d",&(*startCard)->type,&(*startCard)->ratio);
	fscanf(a,"%s\n",(*startCard)->name);
	//============

	for(j=0;j<cnt;j++){
		tempCard = MemoryAllocation_card();
		lastCard->link = tempCard;
		fscanf(a,"%d %d",&tempCard->type,&tempCard->ratio);
		fscanf(a,"%s\n",tempCard->name);
		lastCard = lastCard->link;
	}
	fclose(b);
}

void menuselect(struct menu *start,struct card *startCard){
	char menunum;
	while(1){
		system("cls");
		drawmain();
		gotoxy(93,35);
		printf("메뉴선택:");
		gotoxy(102,35);
		scanf_s("%c",&menunum);
		if(menunum=='7'){//주문
			sells(start,startCard);
		}else if(menunum=='8'){//거래내역조회
			historys();
		}else if(menunum=='4'){//재고량
			stocks(start);
		}else if(menunum=='5'){//목표치 분석
			goals(start);
		}else if(menunum=='1'){//상품등록
			products(start);
		}else if(menunum=='2'){//할인카드등록
			cards(startCard);
		}else if(menunum=='0'){//eod
			eod(start);
		}else if(menunum=='3'){
			saveData_menu(start);
			
		}else{
			//메뉴선택창 바로밑에 잘못 입력했다고 뜨게끔.
			
		}
	}
	
}

int main(){
	struct menu *start,*temp,*temp1;
	struct card *startCard;

	startQueue = (struct menu*)malloc(sizeof(*startQueue));
	lastQueue = startQueue;
	startQueue->link = NULL;
	loadDataAll(&start,&startCard);

	system("mode con:cols=125 lines=40");
	//콘솔창 크기가 변하지 않을때.
	//	바탕화면 내 컴퓨터 아이콘에  마우스 오른쪽을 클릭해 단축 창에서 속성을 선택해
	//1.시스템 등록 정보 창->2.고급->3.환경변수->4.Path(시스템 변수(S)부분)->5.편집
	//6.변수값에 %SystemRoot%\system32;%SystemRoot% 가있는지 확인
	//만약 없다면 변수값을 다지우지마시고
	//맨 앞부분에 %SystemRoot%\system32;%SystemRoot%;
	menuselect(start,startCard);


	//메모리 반환
	temp1=start;
	start=start->link;
	
	
	while(start){
		temp=start;
		start=start->link;
		free(temp);
	}
	start=temp1;
	while(start){
		temp1=start;
		start=start->rlink;
		free(temp1);
	}
	//==========================================
	return 0;
}