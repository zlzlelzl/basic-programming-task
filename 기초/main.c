#include <stdio.h>
#include <windows.h> // Sleep, exit(0) �� system("cls") �� ����ϱ� ���� �������
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 25
struct menu{
	int type;//�������� Ÿ���� ��ǥġ
	int count;
	int price;
	int stock;
	char *name;
	struct menu *link;//��ü�޴� ����Ʈ
	struct menu *rlink;//������� ��Ű�� �ִ� �޴� ����Ʈ
}*lastAll,*lastNow, *startQueue, *lastQueue;
int QueueCount=0;
struct card{
	char *name;
	int type;//�����忡���� ī���� ����
	int ratio;
	struct card * link;
}*lastCard;
//Ŀ���� x,y,��ǥ�� �ű��.
void gotoxy(int x,int y){
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
void saveData_menu(struct menu *start){
	FILE *a=fopen("product.txt","w");//������� ����.
	int j;
	struct menu *temp;
	temp = start;

	fprintf(a,"%d\n",temp->count);//�������� ��ǰ������ ����.

	for(j=0;j<start->count+1;j++){//�������� �ٸ���������� �����Ѵ�.
		fprintf(a,"%d %d %d %d %s\n",temp->type,temp->count,temp->price,temp->stock,temp->name);
		temp=temp->link;
	}
	fclose(a);
}
void saveData_menu_eod(struct menu *start){//������ ������ ���� ���Ͽ� ���� ������ �����.
	struct menu *temp;
	temp = start;
	temp->price=0;//�����Ǹŷ� �ʱ�ȭ
	temp->stock=0;//���� ���� �հ� �ʱ�ȭ
	temp = start->link;
	while(temp){
		temp->count=0;
		temp = temp->link;
	}
	saveData_menu(start);
}
void saveData_card(struct card *startCard){
	FILE *b=fopen("card.txt","w");//������� ����.
	int j;
	struct card *tempCard;
	tempCard = startCard;

	fprintf(b,"%d\n",tempCard->type);//�������� ī�尹���� ����.

	for(j=0;j<startCard->type+1;j++){//�������� �ٸ���������� �����Ѵ�.
		fprintf(b,"%d %d %s\n",tempCard->type,tempCard->ratio,tempCard->name);
		tempCard=tempCard->link;
	}
	fclose(b);
}
//�����ִ� ȭ��� ��ư ȭ�� �и�
void drawmain(){
	int i;
	for(i=0;i<40;i++){
		gotoxy(90,i); printf("��");
	}
	//ù°��
	gotoxy(92,0);
	printf("����������������\n");
	gotoxy(92,1);
	printf("����  Sells   ��\n");
	gotoxy(92,2);
	printf("��            ��\n");
	gotoxy(92,3);
	printf("��    �Ǹ�    ��\n");
	gotoxy(92,4);
	printf("����������������\n");
	gotoxy(108,0);
	printf("����������������\n");
	gotoxy(108,1);
	printf("���� Historys ��\n");
	gotoxy(108,2);
	printf("��            ��\n");
	gotoxy(108,3);
	printf("���ŷ�������ȸ��\n");
	gotoxy(108,4);
	printf("����������������\n");
	//��°��
	gotoxy(92,5);
	printf("����������������\n");
	gotoxy(92,6);
	printf("����  Stocks  ��\n");
	gotoxy(92,7);
	printf("��            ��\n");
	gotoxy(92,8);
	printf("�� �����ȸ ��\n");
	gotoxy(92,9);
	printf("����������������\n");
	gotoxy(108,5);
	printf("����������������\n");
	gotoxy(108,6);
	printf("����  Goals   ��\n");
	gotoxy(108,7);
	printf("��            ��\n");
	gotoxy(108,8);
	printf("�� ��ǥġ�м� ��\n");
	gotoxy(108,9);
	printf("����������������\n");
	//��°��
	gotoxy(92,10);
	printf("����������������\n");
	gotoxy(92,11);
	printf("���� Products ��\n");
	gotoxy(92,12);
	printf("��            ��\n");
	gotoxy(92,13);
	printf("��  ��ǰ���  ��\n");
	gotoxy(92,14);
	printf("����������������\n");
	gotoxy(108,10);
	printf("����������������\n");
	gotoxy(108,11);
	printf("����  Cards   ��\n");
	gotoxy(108,12);
	printf("��            ��\n");
	gotoxy(108,13);
	printf("������ī���Ϧ�\n");
	gotoxy(108,14);
	printf("����������������\n");
	//��°��
	gotoxy(92,15);
	printf("����������������\n");
	gotoxy(92,16);
	printf("����  E.O.D   ��\n");
	gotoxy(92,17);
	printf("��            ��\n");
	gotoxy(92,18);
	printf("��  ��������  ��\n");
	gotoxy(92,19);
	printf("����������������\n");
	gotoxy(108,15);
	printf("����������������\n");
	gotoxy(108,16);
	printf("����  Editor  ��\n");
	gotoxy(108,17);
	printf("��            ��\n");
	gotoxy(108,18);
	printf("�� �������� ��\n");
	gotoxy(108,19);
	printf("����������������\n");
}
struct card* searchCard(int type,struct card *startCard){//���� �޴��� ��ü����Ʈ�� �ִ��� ������ �˻�
	struct card *temp=NULL;
	temp=startCard->link;//ù���� ������� ����
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
void attach_card(int type,int ratio,struct card *startCard){//����Ʈ�ڿ� ��� ���̱�(��ü����Ʈ)
	struct card *temp=NULL;
	//��ü����Ʈ �˻� �� ��� �Ҵ�� ���� ����
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
struct menu* searchAll(int type,struct menu *start){//���� �޴��� ��ü����Ʈ�� �ִ��� ������ �˻�
	struct menu *temp=NULL;
	temp=start->link;//ù���� ������� ����
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
struct menu* searchNow(int type,struct menu *start){//���� �޴��� ���������Ʈ�� �ִ��� ������ �˻�
	struct menu *temp=NULL;
	temp=start->rlink;//ù���� ������� ����
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->rlink;
	}
	return temp;
}
void attach(int type,int num,struct menu *start){//����Ʈ�ڿ� ��� ���̱�(��ü����Ʈ)
	struct menu *temp=NULL,*temp1=NULL;
	//��ü����Ʈ �˻� �� ��� �Ҵ�� ���� ����
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

	//���� ���� �޴� ����Ʈ(������ �ϴܿ� ����ϱ� ����)
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
void drawsells(struct menu *start,struct card *startCard){//�ֹ�ȭ�� �׸���
	struct menu *temp;
	struct card *tempCard;
	int count = start->count;
	int countHalf,i;
	temp=start->link;
	countHalf = count/2 + count%2;//¦���϶� ���� Ȧ���϶� 1�� ���� �޴��� �տ� ����Ѵ�.

	tempCard = startCard->link;


	gotoxy(3,3);
	printf("      �޴�                   ����               �޴�                    ����");
	gotoxy(3,4);
	printf("������������������������������������������������������������������������������������");
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
	printf("����ī��");
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
		
		drawmain();//��ü��� �׸���
		drawsells(start,startCard);//���ʿ� �޴� �׸���
		gotoxy(3,34);
		printf("�޴� �Է� (�޴� ����):");
		if(type>=31 && type<=(startCard->type+30)){
			tempCard = searchCard(type,startCard);
			discount = tempCard->ratio;
		}
		//if(type>21){//������ �ʰ��� �Է�
		//	gotoxy(35,34);
		//	printf("�߸��� �Է��Դϴ�.");
		//}
		if(type>=1 && type<=start->count || type>=31 && type<=(startCard->type+30)){//1��~20�� ������ �޴��� �Է½� ������ �Ʒ�ȭ�鿡 �Ѿ׼��� �ֹ���Ų ��Ȳ�� ������/����ī�� �Է½� ���ε� �ݾױ����ؼ� ȭ�鿡 �ٽ� �ѷ���.
			temp=temp->rlink;//�ʱ���� ������ ���� �ι�° ������ ����.
			i=0;
			sum=0;
			while(temp){
				sum=sum + temp->price*temp->count;//�Ѿ� ���
				if(temp->count != 0){//�ߵ� ��ҵǾ� ������ 0�� �ɰ�� ������� �ʴ´�.
					gotoxy(92,25+i);//������ �Ʒ� ��ġ
					printf("%d.%s",temp->type,temp->name);
					gotoxy(115,25+i);//������ �Ʒ� ��ġ
					printf("%d��",temp->count);
					i++;
				}
				temp=temp->rlink;
			}
			tempsum = sum;
			tempsum = tempsum*discount/100;
			
			gotoxy(92,35);
			printf("��������������������������������");
			gotoxy(92,36);
			printf("�հ� : %d - %d = %d",sum,tempsum,sum - tempsum);
			
		}
		if(type>=1 && type<=start->count){//������� �ȸ� �� �׼� ���
			temp=start->link;//�ʱ���� ������ ���� �ι�° ������ ����.
			start->price=0;
			while(temp){
				start->price=start->price + temp->price*temp->count;//�����忡 �� �׼� ����
				temp=temp->link;
			}
		}
		gotoxy(3,35);
		printf("��������������������������������������������������������������������������������������");
		gotoxy(3,36);
		printf("0 : �����޴� �̵� / 50 : ���� / ��ǰ�� ������ȣ�� �ֹ� /�߰���ҽ� ������ -�ٿ� �ֹ�");
		gotoxy(25,34);
		scanf("%d",&type);
		if(type>=1 && type<=start->count){//1��~20�� ������ �޴��� ����ü ����Ʈ�� ���Խ�Ų��.
			scanf("%d",&num);
			if(num != 0){//������ 0�� �ƴϸ�//0�̸� ����Ʈ�� �߰� ����.
				attach(type,num,start);
				attach_Queue(type,num,start,10);
			}
			
		}else if(type == 50){
			discount = 0;
			deletetempstart=start->rlink;//ù��带 �����ϰ� ��� �޸�����
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,2);
	printf("   ��ǰ��                      ���                    �Ǹŷ�              ���");
	gotoxy(1,3);
	printf("����������������������������������������������������������������������������������������");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(25,i);
		for(j=0;j<temp->stock/10;j++){
			printf("��");
			if(j==9){//�ִ� 10�������� �׸�.
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
		printf("���α���ǰ��");
	}
	
	gotoxy(1,35);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵� / ��� �߰��� ��ǰ������ȣ �Է� �� ���� �Է�\n");
}
void stocks(struct menu *start){
	struct menu *temp1;
	int type,num;
	
	while(1){
		saveData_menu(start);//��������Ȱ� ����
		system("cls");
		drawmain();
		drawstocks(start);
		gotoxy(1,34);
		printf("��� ����(�޴� �߰��Ҽ���):");
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
	float goal=((float)start->price/start->type)*100;//int���̱⶧���� ����ȯ�� �ʿ���.
	int i;
	gotoxy(1,2);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,3);
	printf("   ��ǥ��                      �Ǹž�                ��ǥ�ݾ� - �Ǹűݾ�              ");
	gotoxy(1,4);
	printf("����������������������������������������������������������������������������������������");

	gotoxy(3,5);
	printf("%d",start->type);
	gotoxy(32,5);
	printf("%d",start->price);
	gotoxy(60,5);
	printf("%d",start->type-start->price);



		gotoxy(18,15);
	printf("��������������������������������������");
	gotoxy(18,16);
	printf("����ǥ������                        ��");

	gotoxy(18,17);
	printf("��");
	gotoxy(26,17);
		for(i=0;i<goal/10;i++){
			printf("��");
			if(i==9){//�ִ� 10�������� �׸�.
				break;
			}
	}
	gotoxy(54,17);
	printf("��");
	gotoxy(18,18);
	printf("��                          %.1f%%",goal);
	gotoxy(54,18);
	printf("��");
	gotoxy(18,19);
	printf("��������������������������������������");




	gotoxy(1,34);
	printf("�޴��Է� : ");
	gotoxy(1,35);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵�/ 1 : ��ǥ�� ����");
	
}
void goals(struct menu *start){
	int exit=0,type;//type�� ��ǥġ
	while(1){
		saveData_menu(start);//��������Ȱ� ����
		system("cls");
		drawmain();//��ü��� �׸���
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
void draweod(struct menu *start){//����ڷ� ���
	struct menu *temp;
	int i=4;
	temp = start->link;
	gotoxy(1,1);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,2);
	printf("   ��ǰ��               �Ǹż���               �Ǹž�               ���");
	gotoxy(1,3);
	printf("����������������������������������������������������������������������������������������");
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,++i);
	printf("�� ���� : %d",start->price);
	gotoxy(1,++i);
	printf("��ǥ�ݾ� : %d",start->type);
	gotoxy(1,++i);
	printf("�޼��� : %d%%",start->price / start->type * 100);
	gotoxy(1,34);
	printf("�޴��Է� : ");
	gotoxy(1,35);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵�/ 100 : ��������(������ ��� ������ �ʱ�ȭ �˴ϴ�)");
	

	

}
void eod(struct menu *start){
	int exit=1;//0�� 100�� �ƴѰ��� ����->�����ÿ��� ������ ����ϱ� ����
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
		printf("�޴��Է� : ");
		gotoxy(1,35);
		printf("����������������������������������������������������������������������������������������");
		gotoxy(1,36);
		printf("0 : �����޴� �̵�/ 100 : ��������(������ ��� ������ �ʱ�ȭ �˴ϴ�)");
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,2);
	printf("   ī���                      ������                                 ");
	gotoxy(1,3);
	printf("����������������������������������������������������������������������������������������");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(34,i);
		printf("%d%%",temp->ratio);

	
		temp=temp->link;
		i++;
	}
	gotoxy(1,34);
	printf("�޴��Է� : ");
	gotoxy(1,35);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵�/ 1 : ī�� ��� / 2 : ī�� ���� / 3 : ī�� ����");
}
void cards(struct card *startCard){
	int exit,i,cnt;
	int ratio;
	int type;
	char name[15];
	struct card *temp ,*deletetemp;
	while(1){
		saveData_card(startCard);//��� ī������ �����Ͽ� ��� ����.
		system("cls");
		drawmain();
		drawCards(startCard);
		gotoxy(12,34);
		scanf("%d",&exit);
		if(exit==0){
			break;
		}else if(exit == 1){//ī����
			gotoxy(1,31);
			printf("ī��� �Է�:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("������ �Է�:");
			scanf("%d",&ratio);

			temp = MemoryAllocation_card();
			strcpy(temp->name,name);
			//temp->name = name;
			temp->ratio = ratio;
			temp->type = ++startCard->type+30;//�� ī����� 1�� ���� Ÿ���� �����ϰ� �� �޴��� ���� ������Ų��.
			lastCard->link = temp;
			lastCard = temp;
			lastCard->link=NULL;
		}else if(exit == 2){//ī�����
			gotoxy(1,31);
			printf("ī�������ȣ �Է�:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){
				gotoxy(1,32);
				printf("ī��� �Է�:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("������ �Է�:");
				scanf("%d",&ratio);
				strcpy(temp->name,name);
				temp->ratio = ratio;
			}
		}else if(exit == 3){//ī�����
			gotoxy(1,31);
			printf("ī�������ȣ �Է�:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){//Ÿ���� ���� ��尡 �ִٸ�
				deletetemp = startCard;//���������� ������ߵǹǷ� start���� ����
				cnt=startCard->type;//������ ������ cnt�� ����
				startCard->type--;//�����Ǵϱ� 1����
				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//������尡 temp�� ���ٸ� �� ����� ��ũ�� temp�� ��ũ�� ����Ű�� ���� ����Ű�� �Ѵ�.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//�ǵ��� ��尡 �����ƴٸ� ��������带 ����Ű�� �����͸� �Ű������.
							lastCard=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//type�� �ٽ� ����
				deletetemp=startCard->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i+30;//type�� �ٽ� ����
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,2);
	printf("   ��ǰ��                      ��  ��                    �Ǹž�             ����ī��");
	gotoxy(1,3);
	printf("����������������������������������������������������������������������������������������");
	if(temp == NULL){
		gotoxy(1,i);
		printf("�ֱ� �ŷ� ������ �����ϴ�.");
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵�\n");
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
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,2);
	printf("   ��ǰ��                      �Ǹž�                    ���             ");
	gotoxy(1,3);
	printf("����������������������������������������������������������������������������������������");
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
	printf("�޴��Է� : ");
	gotoxy(1,35);
	printf("����������������������������������������������������������������������������������������");
	gotoxy(1,36);
	printf("0 : �����޴� �̵�/ 1 : ��ǰ ��� / 2 : ��ǰ ���� / 3 : ��ǰ ����");
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
		}else if(exit == 1){//��ǰ���
			gotoxy(1,31);
			printf("��ǰ�� �Է�:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("���� �Է�:");
			scanf("%d",&price);
			gotoxy(1,33);
			printf("��� �Է�:");
			scanf("%d",&stock);
			temp = MemoryAllocation();
			strcpy(temp->name,name);
			temp->price = price;
			temp->stock = stock;
			temp->type = ++start->count;//�� �޴����� 1�� ���� Ÿ���� �����ϰ� �� �޴��� ���� ������Ų��.
			temp->count=0;
			lastAll->link = temp;
			lastAll = temp;
			lastAll->link=NULL;
		}else if(exit == 2){//��ǰ����
			gotoxy(1,31);
			printf("��ǰ������ȣ �Է�:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){
				gotoxy(1,32);
				printf("��ǰ�� �Է�:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("���� �Է�:");
				scanf("%d",&price);
				temp->name = name;
				temp->price = price;
			}
		}else if(exit == 3){//��ǰ����
			gotoxy(1,31);
			printf("��ǰ������ȣ �Է�:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){//Ÿ���� ���� ��尡 �ִٸ�
				deletetemp = start;//���������� ������ߵǹǷ� start���� ����
				cnt=start->count;//������ ������ cnt�� ����
				start->count--;

				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//������尡 temp�� ���ٸ� �� ����� ��ũ�� temp�� ��ũ�� ����Ű�� ���� ����Ű�� �Ѵ�.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//�ǵ��� ��尡 �����ƴٸ� ��������带 ����Ű�� �����͸� �Ű������.
							lastAll=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//Ÿ���� �ٽ� �����ϴ� �κ�. �߰��� ������ ���/
				deletetemp=start->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i;//type�� �ٽ� ����
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
	FILE *a=fopen("product.txt","a");//������ ���°��� �������� ������ְ� �ִ°��� �׳� �����ٰ� �ݴ´�.
	FILE *b=fopen("card.txt","a");
	fclose(a);//�б��带 �������� �����Ų��.
	fclose(b);

	a=fopen("product.txt","r");//�б���� ����. �̷��� �������ν� ���������Ͱ� �Ǿտ� ��ġ.

	*start = MemoryAllocation();
	lastAll=*start;
	lastNow=*start;
	
	fscanf(a,"%d",&cnt);

	//������ ����
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
	fclose(a);//��ǰ���� �о��


	b=fopen("card.txt","r");//�б���� ����. ī������ �о�����
	*startCard = MemoryAllocation_card();
	lastCard=*startCard;

	fscanf(a,"%d",&cnt);

	//������ ����
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
		printf("�޴�����:");
		gotoxy(102,35);
		scanf_s("%c",&menunum);
		if(menunum=='7'){//�ֹ�
			sells(start,startCard);
		}else if(menunum=='8'){//�ŷ�������ȸ
			historys();
		}else if(menunum=='4'){//���
			stocks(start);
		}else if(menunum=='5'){//��ǥġ �м�
			goals(start);
		}else if(menunum=='1'){//��ǰ���
			products(start);
		}else if(menunum=='2'){//����ī����
			cards(startCard);
		}else if(menunum=='0'){//eod
			eod(start);
		}else if(menunum=='3'){
			saveData_menu(start);
			
		}else{
			//�޴�����â �ٷιؿ� �߸� �Է��ߴٰ� �߰Բ�.
			
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
	//�ܼ�â ũ�Ⱑ ������ ������.
	//	����ȭ�� �� ��ǻ�� �����ܿ�  ���콺 �������� Ŭ���� ���� â���� �Ӽ��� ������
	//1.�ý��� ��� ���� â->2.���->3.ȯ�溯��->4.Path(�ý��� ����(S)�κ�)->5.����
	//6.�������� %SystemRoot%\system32;%SystemRoot% ���ִ��� Ȯ��
	//���� ���ٸ� �������� �����������ð�
	//�� �պκп� %SystemRoot%\system32;%SystemRoot%;
	menuselect(start,startCard);


	//�޸� ��ȯ
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