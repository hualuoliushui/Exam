//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <string>
//#include <map>
//#include <hash_map>  
//#include <stack>
//#include <queue>
//
//using namespace std;
//
//char strRelation[] =
//"A B ͬѧ ͬ�� ͬ��\n"
//"C D ͬ��\n"
//"E F ͬѧ\n"
//"G H ͬ��\n"
//"I J ͬ��\n"
//"H I ͬѧ ͬ��\n"
//"B J ͬ��\n";
///*
//���룺A,B,1
//�����true //A��B��ͬѧ��ͬ�¡�ͬ�磬ά��Ϊ1��
//
//���룺A,B,2
//�����true //A��B��ͬѧ��ͬ�¡�ͬ�磬ά��Ϊ1����ȻҲ��ά��2�ռ��ڣ�
//
//���룺A,D,2
//�����false //A��Dû���κι�ϵ��
//
//���룺A,J,2
//�����true //A ��B��ͬѧ��B��J��ͬ�磬A��J�Ĺ�ϵά����2��
//
//���룺A,I,2
//�����false //A ��B��ͬѧ��B��J��ͬ�磬J��I��ͬ�£�A��I�Ĺ�ϵά����3��ά�Ȳ�������Ϊ2�������㣻
//
//���룺A,I,3
//�����true //A ��B��ͬѧ��B��J��ͬ�磬J��I��ͬ�£�A��I�Ĺ�ϵά����3��ά�Ȳ�������Ϊ3�����㣻
//*/
//
//bool IsRelationSpace(const char * H1, const char * H2, int DimensionDistance)
//{
//	vector<vector<char>> relations;
//
//	char* temp = strRelation;
//	while (*temp != '\0'){
//		char h1 = *temp;
//		temp += 2;
//		char h2 = *temp;
//
//		vector<char> char_pair;
//		char_pair.push_back(h1);
//		char_pair.push_back(h2);
//
//		relations.push_back(char_pair);
//
//		while (*temp != '\n')temp++;
//		temp++;
//	}
//
//	int realDim = 0;
//	bool hasRelation = false;
//
//	queue<char> relations_h1;
//
//	vector<char> discards;
//
//	relations_h1.push(*H1);
//	int curLevel = 1;
//	int nextLevel = 0;
//
//	map<char, char>::iterator it;
//	while (!relations_h1.empty()){
//		char temp = relations_h1.front();
//		relations_h1.pop();
//
//		bool isDiscard = false;
//		for (int i = 0; i < discards.size(); i++){
//			if (discards[i] == temp){
//				isDiscard = true;
//				break;
//			}
//		}
//
//
//		if (!isDiscard){
//			for (int i = 0; i < relations.size(); i++){
//				if (relations[i][0] == temp){
//					if (relations[i][1] == *H2){
//						hasRelation = true;
//						break;
//					}
//					else{
//						relations_h1.push(relations[i][1]);
//						nextLevel++;
//					}
//				}
//				else if (relations[i][1] == temp){
//					if (relations[i][0] == *H2){
//						hasRelation = true;
//						break;
//					}
//					else{
//						relations_h1.push(relations[i][0]);
//						nextLevel++;
//					}
//				}
//			}
//			discards.push_back(temp);
//		}
//
//		curLevel--;
//		if (curLevel == 0){
//			curLevel = nextLevel;
//			nextLevel = 0;
//			realDim++;
//			if (hasRelation){
//				break;
//			}
//		}
//	}
//
//	if (hasRelation && realDim <= DimensionDistance){
//		return true;
//	}
//
//	return false;
//}
//
////int main(int argc, char* argv[])
////{
////	char name1[100] = "";
////	char name2[100] = "";
////	int RelationDistance = 0;
////
////	while (std::cin >> name1 >> name2 >> RelationDistance){
////		bool bRet = IsRelationSpace(name1, name2, RelationDistance);
////
////		if (bRet){
////			printf("true");
////		}
////		else{
////			printf("false");
////		}
////	}
////	return 0;
////}