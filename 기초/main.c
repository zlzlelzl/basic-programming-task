#include <stdio.h>
#include <windows.h> // Sleep, exit(0) 婁 system("cls") 蒂 餌辨ж晦 嬪и ④渦だ橾
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 25
struct menu{
	int type;//④渦喻萄曖 顫殮擎 跡ル纂
	int count;
	int price;
	int stock;
	char *name;
	struct menu *link;//瞪羹詭景 葬蝶お
	struct menu *rlink;//⑷營堅偌檜 衛酈堅 氈朝 詭景 葬蝶お
}*lastAll,*lastNow, *startQueue, *lastQueue;
int QueueCount=0;
struct card{
	char *name;
	int type;//④渦喻萄縑憮朝 蘋萄曖 熱榆
	int ratio;
	struct card * link;
}*lastCard;
//醴憮蒂 x,y,謝ル煎 衡曹棻.
void gotoxy(int x,int y){
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}
void saveData_menu(struct menu *start){
	FILE *a=fopen("product.txt","w");//噙晦賅萄煎 翱棻.
	int j;
	struct menu *temp;
	temp = start;

	fprintf(a,"%d\n",temp->count);//④渦喻萄曖 鼻ヶ偎熱蒂 盪濰.

	for(j=0;j<start->count+1;j++){//④渦喻萄曖 棻艇薑爾菟梱雖 盪濰и棻.
		fprintf(a,"%d %d %d %d %s\n",temp->type,temp->count,temp->price,temp->stock,temp->name);
		temp=temp->link;
	}
	fclose(a);
}
void saveData_menu_eod(struct menu *start){//棻擠陳 艙機擊 嬪п 旎橾縑 渠и 薑爾蒂 雖遴棻.
	struct menu *temp;
	temp = start;
	temp->price=0;//橾橾っ衙榆 蟾晦��
	temp->stock=0;//⑷營 堅偌曖 м啗 蟾晦��
	temp = start->link;
	while(temp){
		temp->count=0;
		temp = temp->link;
	}
	saveData_menu(start);
}
void saveData_card(struct card *startCard){
	FILE *b=fopen("card.txt","w");//噙晦賅萄煎 翱棻.
	int j;
	struct card *tempCard;
	tempCard = startCard;

	fprintf(b,"%d\n",tempCard->type);//④渦喻萄曖 蘋萄偎熱蒂 盪濰.

	for(j=0;j<startCard->type+1;j++){//④渦喻萄曖 棻艇薑爾菟梱雖 盪濰и棻.
		fprintf(b,"%d %d %s\n",tempCard->type,tempCard->ratio,tempCard->name);
		tempCard=tempCard->link;
	}
	fclose(b);
}
//爾罹輿朝 �飛敿� 幗が �飛� 碟葬
void drawmain(){
	int i;
	for(i=0;i<40;i++){
		gotoxy(90,i); printf("弛");
	}
	//羅簞還
	gotoxy(92,0);
	printf("忙式式式式式式忖\n");
	gotoxy(92,1);
	printf("弛刮  Sells   弛\n");
	gotoxy(92,2);
	printf("弛            弛\n");
	gotoxy(92,3);
	printf("弛    っ衙    弛\n");
	gotoxy(92,4);
	printf("戌式式式式式式戎\n");
	gotoxy(108,0);
	printf("忙式式式式式式忖\n");
	gotoxy(108,1);
	printf("弛制 Historys 弛\n");
	gotoxy(108,2);
	printf("弛            弛\n");
	gotoxy(108,3);
	printf("弛剪楚頂羲褻�蒂兝n");
	gotoxy(108,4);
	printf("戌式式式式式式戎\n");
	//萃簞還
	gotoxy(92,5);
	printf("忙式式式式式式忖\n");
	gotoxy(92,6);
	printf("弛刷  Stocks  弛\n");
	gotoxy(92,7);
	printf("弛            弛\n");
	gotoxy(92,8);
	printf("弛 營堅榆褻�� 弛\n");
	gotoxy(92,9);
	printf("戌式式式式式式戎\n");
	gotoxy(108,5);
	printf("忙式式式式式式忖\n");
	gotoxy(108,6);
	printf("弛刺  Goals   弛\n");
	gotoxy(108,7);
	printf("弛            弛\n");
	gotoxy(108,8);
	printf("弛 跡ル纂碟戮 弛\n");
	gotoxy(108,9);
	printf("戌式式式式式式戎\n");
	//撢簞還
	gotoxy(92,10);
	printf("忙式式式式式式忖\n");
	gotoxy(92,11);
	printf("弛函 Products 弛\n");
	gotoxy(92,12);
	printf("弛            弛\n");
	gotoxy(92,13);
	printf("弛  鼻ヶ蛔煙  弛\n");
	gotoxy(92,14);
	printf("戌式式式式式式戎\n");
	gotoxy(108,10);
	printf("忙式式式式式式忖\n");
	gotoxy(108,11);
	printf("弛刻  Cards   弛\n");
	gotoxy(108,12);
	printf("弛            弛\n");
	gotoxy(108,13);
	printf("弛й檣蘋萄蛔煙弛\n");
	gotoxy(108,14);
	printf("戌式式式式式式戎\n");
	//喘簞還
	gotoxy(92,15);
	printf("忙式式式式式式忖\n");
	gotoxy(92,16);
	printf("弛佾  E.O.D   弛\n");
	gotoxy(92,17);
	printf("弛            弛\n");
	gotoxy(92,18);
	printf("弛  艙機葆馬  弛\n");
	gotoxy(92,19);
	printf("戌式式式式式式戎\n");
	gotoxy(108,15);
	printf("忙式式式式式式忖\n");
	gotoxy(108,16);
	printf("弛券  Editor  弛\n");
	gotoxy(108,17);
	printf("弛            弛\n");
	gotoxy(108,18);
	printf("弛 虜萇餌塋菟 弛\n");
	gotoxy(108,19);
	printf("戌式式式式式式戎\n");
}
struct card* searchCard(int type,struct card *startCard){//偽擎 詭景陛 瞪羹葬蝶お縑 氈朝雖 橈朝雖 匐餌
	struct card *temp=NULL;
	temp=startCard->link;//羅喻萄朝 ④渦喻萄塭憮 貍堅
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
void attach_card(int type,int ratio,struct card *startCard){//葬蝶お菴縑 喻萄 稱檜晦(瞪羹葬蝶お)
	struct card *temp=NULL;
	//瞪羹葬蝶お 匐儀 �� 喻萄 й渡塽 熱榆 隸陛
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
struct menu* searchAll(int type,struct menu *start){//偽擎 詭景陛 瞪羹葬蝶お縑 氈朝雖 橈朝雖 匐餌
	struct menu *temp=NULL;
	temp=start->link;//羅喻萄朝 ④渦喻萄塭憮 貍堅
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->link;
	}
	return temp;
}
struct menu* searchNow(int type,struct menu *start){//偽擎 詭景陛 ⑷營堅偌葬蝶お縑 氈朝雖 橈朝雖 匐餌
	struct menu *temp=NULL;
	temp=start->rlink;//羅喻萄朝 ④渦喻萄塭憮 貍堅
	while(temp){
		if(temp->type == type){
			break;
		}
		temp=temp->rlink;
	}
	return temp;
}
void attach(int type,int num,struct menu *start){//葬蝶お菴縑 喻萄 稱檜晦(瞪羹葬蝶お)
	struct menu *temp=NULL,*temp1=NULL;
	//瞪羹葬蝶お 匐儀 �� 喻萄 й渡塽 熱榆 隸陛
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

	//⑷營 堅偌曖 詭景 葬蝶お(螃艇薹 ж欽縑 轎溘ж晦 嬪л)
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
void drawsells(struct menu *start,struct card *startCard){//輿僥�飛� 斜葬晦
	struct menu *temp;
	struct card *tempCard;
	int count = start->count;
	int countHalf,i;
	temp=start->link;
	countHalf = count/2 + count%2;//礎熱橾隆 瞰奩 �汝鶺炩� 1偃 號擎 詭景蒂 擅縑 轎溘и棻.

	tempCard = startCard->link;


	gotoxy(3,3);
	printf("      詭景                   陛問               詭景                    陛問");
	gotoxy(3,4);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
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
	printf("й檣蘋萄");
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
		
		drawmain();//瞪羹賅曄 斜葬晦
		drawsells(start,startCard);//寰薹縑 詭景 斜葬晦
		gotoxy(3,34);
		printf("詭景 殮溘 (詭景 熱榆):");
		if(type>=31 && type<=(startCard->type+30)){
			tempCard = searchCard(type,startCard);
			discount = tempCard->ratio;
		}
		//if(type>21){//彰嬪蒂 蟾婁и 殮溘
		//	gotoxy(35,34);
		//	printf("澀跤脹 殮溘殮棲棻.");
		//}
		if(type>=1 && type<=start->count || type>=31 && type<=(startCard->type+30)){//1廓~20廓 餌檜曖 詭景蒂 殮溘衛 螃艇薹 嬴楚�飛橦� 識擋熱塽 輿僥衛鑑 ⑷�窕� 爾罹邀/й檣蘋萄 殮溘衛 й檣脹 旎擋梱雖п憮 �飛橦� 棻衛 銑溥邀.
			temp=temp->rlink;//蟾晦喻萄朝 ④渦喻萄 評塭憮 舒廓簞 喻萄睡攪 衛濛.
			i=0;
			sum=0;
			while(temp){
				sum=sum + temp->price*temp->count;//識擋 啗骯
				if(temp->count != 0){//醞紫 鏃模腎橫 熱榆檜 0檜 腆唳辦 轎溘ж雖 彊朝棻.
					gotoxy(92,25+i);//螃艇薹 嬴楚 嬪纂
					printf("%d.%s",temp->type,temp->name);
					gotoxy(115,25+i);//螃艇薹 嬴楚 嬪纂
					printf("%d偃",temp->count);
					i++;
				}
				temp=temp->rlink;
			}
			tempsum = sum;
			tempsum = tempsum*discount/100;
			
			gotoxy(92,35);
			printf("式式式式式式式式式式式式式式式式");
			gotoxy(92,36);
			printf("м啗 : %d - %d = %d",sum,tempsum,sum - tempsum);
			
		}
		if(type>=1 && type<=start->count){//⑷營梱雖 つ萼 識 擋熱 啗骯
			temp=start->link;//蟾晦喻萄朝 ④渦喻萄 評塭憮 舒廓簞 喻萄睡攪 衛濛.
			start->price=0;
			while(temp){
				start->price=start->price + temp->price*temp->count;//④渦喻萄縑 識 擋熱 盪濰
				temp=temp->link;
			}
		}
		gotoxy(3,35);
		printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
		gotoxy(3,36);
		printf("0 : 鼻嬪詭景 檜翕 / 50 : 唸薯 / 薯ヶ曖 堅嶸廓�ㄦ� 輿僥 /醞除鏃模衛 偎熱縑 -稱罹 輿僥");
		gotoxy(25,34);
		scanf("%d",&type);
		if(type>=1 && type<=start->count){//1廓~20廓 餌檜曖 詭景虜 掘褻羹 葬蝶お縑 んл衛鑑棻.
			scanf("%d",&num);
			if(num != 0){//熱榆檜 0檜 嬴棲賊//0檜賊 葬蝶お縑 蹺陛 寰л.
				attach(type,num,start);
				attach_Queue(type,num,start,10);
			}
			
		}else if(type == 50){
			discount = 0;
			deletetempstart=start->rlink;//羅喻萄蒂 薯諼ж堅 賅舒 詭賅葬п薯
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,2);
	printf("   薯ヶ貲                      營堅榆                    っ衙榆              綠堅");
	gotoxy(1,3);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(25,i);
		for(j=0;j<temp->stock/10;j++){
			printf("﹥");
			if(j==9){//譆渠 10偃梱雖虜 斜葡.
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
		printf("≠檣晦薯ヶ≠");
	}
	
	gotoxy(1,35);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕 / 營堅榆 蹺陛衛 薯ヶ堅嶸廓�� 殮溘 �� 熱榆 殮溘\n");
}
void stocks(struct menu *start){
	struct menu *temp1;
	int type,num;
	
	while(1){
		saveData_menu(start);//頂辨熱薑脹剪 盪濰
		system("cls");
		drawmain();
		drawstocks(start);
		gotoxy(1,34);
		printf("營堅榆 熱薑(詭景 蹺陛й熱榆):");
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
	float goal=((float)start->price/start->type)*100;//int⑽檜晦陽僥縑 ⑽滲�素� в蹂л.
	int i;
	gotoxy(1,2);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,3);
	printf("   跡ル擋                      っ衙擋                跡ル旎擋 - っ衙旎擋              ");
	gotoxy(1,4);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");

	gotoxy(3,5);
	printf("%d",start->type);
	gotoxy(32,5);
	printf("%d",start->price);
	gotoxy(60,5);
	printf("%d",start->type-start->price);



		gotoxy(18,15);
	printf("忙式式式式式式式式式式式式式式式式式忖");
	gotoxy(18,16);
	printf("弛跡ル啪檜雖                        弛");

	gotoxy(18,17);
	printf("弛");
	gotoxy(26,17);
		for(i=0;i<goal/10;i++){
			printf("﹥");
			if(i==9){//譆渠 10偃梱雖虜 斜葡.
				break;
			}
	}
	gotoxy(54,17);
	printf("弛");
	gotoxy(18,18);
	printf("弛                          %.1f%%",goal);
	gotoxy(54,18);
	printf("弛");
	gotoxy(18,19);
	printf("戌式式式式式式式式式式式式式式式式式戎");




	gotoxy(1,34);
	printf("詭景殮溘 : ");
	gotoxy(1,35);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕/ 1 : 跡ル擋 滲唳");
	
}
void goals(struct menu *start){
	int exit=0,type;//type檜 跡ル纂
	while(1){
		saveData_menu(start);//頂辨熱薑脹剪 盪濰
		system("cls");
		drawmain();//瞪羹賅曄 斜葬晦
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
void draweod(struct menu *start){//賅萇濠猿 轎溘
	struct menu *temp;
	int i=4;
	temp = start->link;
	gotoxy(1,1);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,2);
	printf("   薯ヶ貲               っ衙熱榆               っ衙擋               營堅榆");
	gotoxy(1,3);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,++i);
	printf("識 衙轎 : %d",start->price);
	gotoxy(1,++i);
	printf("跡ル旎擋 : %d",start->type);
	gotoxy(1,++i);
	printf("殖撩睦 : %d%%",start->price / start->type * 100);
	gotoxy(1,34);
	printf("詭景殮溘 : ");
	gotoxy(1,35);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕/ 100 : 艙機葆馬(葆馬衛 賅萇 薑爾陛 蟾晦�� 腌棲棻)");
	

	

}
void eod(struct menu *start){
	int exit=1;//0紫 100紫 嬴棋高擊 撲薑->葆馬衛縑虜 薑爾蒂 轎溘ж晦 陽僥
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
		printf("詭景殮溘 : ");
		gotoxy(1,35);
		printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
		gotoxy(1,36);
		printf("0 : 鼻嬪詭景 檜翕/ 100 : 艙機葆馬(葆馬衛 賅萇 薑爾陛 蟾晦�� 腌棲棻)");
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,2);
	printf("   蘋萄貲                      й檣徽                                 ");
	gotoxy(1,3);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	while(temp){
		gotoxy(1,i);
		printf("%d.%s",temp->type,temp->name);
		gotoxy(34,i);
		printf("%d%%",temp->ratio);

	
		temp=temp->link;
		i++;
	}
	gotoxy(1,34);
	printf("詭景殮溘 : ");
	gotoxy(1,35);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕/ 1 : 蘋萄 蛔煙 / 2 : 蘋萄 熱薑 / 3 : 蘋萄 餉薯");
}
void cards(struct card *startCard){
	int exit,i,cnt;
	int ratio;
	int type;
	char name[15];
	struct card *temp ,*deletetemp;
	while(1){
		saveData_card(startCard);//賅萇 蘋萄薑爾 熱薑ж罹 啗樓 盪濰.
		system("cls");
		drawmain();
		drawCards(startCard);
		gotoxy(12,34);
		scanf("%d",&exit);
		if(exit==0){
			break;
		}else if(exit == 1){//蘋萄蛔煙
			gotoxy(1,31);
			printf("蘋萄貲 殮溘:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("й檣徽 殮溘:");
			scanf("%d",&ratio);

			temp = MemoryAllocation_card();
			strcpy(temp->name,name);
			//temp->name = name;
			temp->ratio = ratio;
			temp->type = ++startCard->type+30;//識 蘋萄熱曖 1擊 渦п 顫殮擊 雖薑ж堅 識 詭景熱 傳и 隸陛衛鑑棻.
			lastCard->link = temp;
			lastCard = temp;
			lastCard->link=NULL;
		}else if(exit == 2){//蘋萄熱薑
			gotoxy(1,31);
			printf("蘋萄堅嶸廓�� 殮溘:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){
				gotoxy(1,32);
				printf("蘋萄貲 殮溘:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("й檣徽 殮溘:");
				scanf("%d",&ratio);
				strcpy(temp->name,name);
				temp->ratio = ratio;
			}
		}else if(exit == 3){//蘋萄餉薯
			gotoxy(1,31);
			printf("蘋萄堅嶸廓�� 殮溘:");
			scanf("%d",&type);
			temp=searchCard(type,startCard);
			if(temp){//顫殮檜 偽擎 喻萄陛 氈棻賊
				deletetemp = startCard;//棻擠喻萄睡攪 髦よ瑭撿腎嘎煎 start睡攪 衛濛
				cnt=startCard->type;//⑷營曖 偎熱蒂 cnt縑 盪濰
				startCard->type--;//餉薯腎棲梱 1馬模
				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//棻擠喻萄陛 temp諦 偽棻賊 斜 喻萄曖 葭觼蒂 temp曖 葭觼陛 陛葬酈朝 夠擊 陛葬酈啪 и棻.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//裔菴曖 喻萄陛 餉薯腑棻賊 葆雖虞喻萄蒂 陛葬酈朝 ん檣攪蒂 衡啖醜撿л.
							lastCard=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//type擊 棻衛 撲薑
				deletetemp=startCard->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i+30;//type擊 棻衛 撲薑
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,2);
	printf("   薯ヶ貲                      熱  榆                    っ衙擋             й檣蘋萄");
	gotoxy(1,3);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	if(temp == NULL){
		gotoxy(1,i);
		printf("譆斬 剪楚 頂羲檜 橈蝗棲棻.");
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕\n");
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
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,2);
	printf("   薯ヶ貲                      っ衙擋                    營堅榆             ");
	gotoxy(1,3);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
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
	printf("詭景殮溘 : ");
	gotoxy(1,35);
	printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	gotoxy(1,36);
	printf("0 : 鼻嬪詭景 檜翕/ 1 : 薯ヶ 蛔煙 / 2 : 薯ヶ 熱薑 / 3 : 薯ヶ 餉薯");
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
		}else if(exit == 1){//薯ヶ蛔煙
			gotoxy(1,31);
			printf("薯ヶ貲 殮溘:");
			scanf("%s",name);
			gotoxy(1,32);
			printf("陛問 殮溘:");
			scanf("%d",&price);
			gotoxy(1,33);
			printf("營堅榆 殮溘:");
			scanf("%d",&stock);
			temp = MemoryAllocation();
			strcpy(temp->name,name);
			temp->price = price;
			temp->stock = stock;
			temp->type = ++start->count;//識 詭景熱曖 1擊 渦п 顫殮擊 雖薑ж堅 識 詭景熱 傳и 隸陛衛鑑棻.
			temp->count=0;
			lastAll->link = temp;
			lastAll = temp;
			lastAll->link=NULL;
		}else if(exit == 2){//薯ヶ熱薑
			gotoxy(1,31);
			printf("薯ヶ堅嶸廓�� 殮溘:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){
				gotoxy(1,32);
				printf("薯ヶ貲 殮溘:");
				scanf("%s",name);
				gotoxy(1,33);
				printf("陛問 殮溘:");
				scanf("%d",&price);
				temp->name = name;
				temp->price = price;
			}
		}else if(exit == 3){//薯ヶ餉薯
			gotoxy(1,31);
			printf("薯ヶ堅嶸廓�� 殮溘:");
			scanf("%d",&type);
			temp=searchAll(type,start);
			if(temp){//顫殮檜 偽擎 喻萄陛 氈棻賊
				deletetemp = start;//棻擠喻萄睡攪 髦よ瑭撿腎嘎煎 start睡攪 衛濛
				cnt=start->count;//⑷營曖 偎熱蒂 cnt縑 盪濰
				start->count--;

				for(i=0;i<cnt;i++){
					if(deletetemp->link == temp){//棻擠喻萄陛 temp諦 偽棻賊 斜 喻萄曖 葭觼蒂 temp曖 葭觼陛 陛葬酈朝 夠擊 陛葬酈啪 и棻.
						deletetemp->link = temp->link;
						free(temp);
						if(!deletetemp->link){//裔菴曖 喻萄陛 餉薯腑棻賊 葆雖虞喻萄蒂 陛葬酈朝 ん檣攪蒂 衡啖醜撿л.
							lastAll=deletetemp;
						}
					}	
					deletetemp=deletetemp->link;
				}

				//顫殮擊 棻衛 撲薑ж朝 睡碟. 醞除縑 餉薯腆 唳辦/
				deletetemp=start->link;
				i=1;
				while(deletetemp){
					deletetemp->type = i;//type擊 棻衛 撲薑
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
	FILE *a=fopen("product.txt","a");//だ橾檜 橈朝唳辦朝 綴だ橾擊 虜菟橫輿堅 氈朝唳辦朝 斜傖 翮歷棻陛 殘朝棻.
	FILE *b=fopen("card.txt","a");
	fclose(a);//檗晦賅萄蒂 翮晦嬪п 褒ч衛鑑棻.
	fclose(b);

	a=fopen("product.txt","r");//檗晦賅萄煎 翱棻. 檜溢啪 п邀戲煎賦 だ橾ん檣攪陛 裔擅縑 嬪纂.

	*start = MemoryAllocation();
	lastAll=*start;
	lastNow=*start;
	
	fscanf(a,"%d",&cnt);

	//④渦喻萄 盪濰
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
	fclose(a);//薯ヶ薑爾 檗橫爾晦


	b=fopen("card.txt","r");//檗晦賅萄煎 翱棻. 蘋萄薑爾 檗橫爾晦衛濛
	*startCard = MemoryAllocation_card();
	lastCard=*startCard;

	fscanf(a,"%d",&cnt);

	//④渦喻萄 盪濰
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
		printf("詭景摹鷗:");
		gotoxy(102,35);
		scanf_s("%c",&menunum);
		if(menunum=='7'){//輿僥
			sells(start,startCard);
		}else if(menunum=='8'){//剪楚頂羲褻��
			historys();
		}else if(menunum=='4'){//營堅榆
			stocks(start);
		}else if(menunum=='5'){//跡ル纂 碟戮
			goals(start);
		}else if(menunum=='1'){//鼻ヶ蛔煙
			products(start);
		}else if(menunum=='2'){//й檣蘋萄蛔煙
			cards(startCard);
		}else if(menunum=='0'){//eod
			eod(start);
		}else if(menunum=='3'){
			saveData_menu(start);
			
		}else{
			//詭景摹鷗璽 夥煎壽縑 澀跤 殮溘ц棻堅 嗑啪莠.
			
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
	//夔樂璽 觼晦陛 滲ж雖 彊擊陽.
	//	夥鰻�飛� 頂 闡У攪 嬴檜夔縑  葆辦蝶 螃艇薹擊 贗葛п 欽蹴 璽縑憮 樓撩擊 摹鷗п
	//1.衛蝶蠱 蛔煙 薑爾 璽->2.堅晝->3.�秣皞紡�->4.Path(衛蝶蠱 滲熱(S)睡碟)->5.ら餵
	//6.滲熱高縑 %SystemRoot%\system32;%SystemRoot% 陛氈朝雖 �挫�
	//虜擒 橈棻賊 滲熱高擊 棻雖辦雖葆衛堅
	//裔 擅睡碟縑 %SystemRoot%\system32;%SystemRoot%;
	menuselect(start,startCard);


	//詭賅葬 奩��
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