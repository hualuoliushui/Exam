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
//"A B 同学 同事 同乡\n"
//"C D 同乡\n"
//"E F 同学\n"
//"G H 同姓\n"
//"I J 同事\n"
//"H I 同学 同乡\n"
//"B J 同乡\n";
///*
//输入：A,B,1
//输出：true //A和B是同学、同事、同乡，维度为1；
//
//输入：A,B,2
//输出：true //A和B是同学、同事、同乡，维度为1，当然也在维度2空间内；
//
//输入：A,D,2
//输出：false //A和D没有任何关系；
//
//输入：A,J,2
//输出：true //A 和B是同学，B和J是同乡，A和J的关系维度是2；
//
//输入：A,I,2
//输出：false //A 和B是同学，B和J是同乡，J和I是同事，A和I的关系维度是3；维度参数限制为2，不满足；
//
//输入：A,I,3
//输出：true //A 和B是同学，B和J是同乡，J和I是同事，A和I的关系维度是3；维度参数限制为3，满足；
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