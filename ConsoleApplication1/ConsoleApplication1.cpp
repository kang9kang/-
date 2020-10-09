#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

#include <string>
#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;
void readFileJson(); //从文件中读取JSON，一个存储了JSON格式字符串的文件
int main(int argc, char* argv[])
{
	readFileJson();
	system("pause");
	return 0;
}
//从文件中读取JSON
void readFileJson()
{
	Json::Reader reader;
	Json::Value root;
	
	//从文件中读取，保证当前文件有test.json文件
	ifstream in("test.json", ios::binary);
	//in.open("test.json", ios::binary);
	if (!in.is_open())
	{
		cout << "Error opening file\n";
		return;
	}
	/*
	//test.json内容如下：
	{
		"name":"Tsybius",
		"age":23,
		"sex_is_male":true,
		"partner":
		{
			"partner_name":"Galatea",
			"partner_age":21,
			"partner_sex_is_male":false
		},
		"achievement":["ach1","ach2","ach3"]
	}
	*/
	if (reader.parse(in, root))
	{
		//读取根节点信息
		/*string name = root["name"].asString();
		int age = root["age"].asInt();
		bool sex_is_male = root["sex_is_male"].asBool();
		cout << "My name is " << name << endl;
		cout << "I'm " << age << " years old" << endl;
		cout << "I'm a " << (sex_is_male ? "man" : "woman") << endl;*/
		//读取子节点信息
		/*string partner_name = root["partner"]["partner_name"].asString();
		int partner_age = root["partner"]["partner_age"].asInt();
		bool partner_sex_is_male = root["partner"]["partner_sex_is_male"].asBool();
		cout << "My partner's name is " << partner_name << endl;
		cout << (partner_sex_is_male ? "he" : "she") << " is "
			<< partner_age << " years old" << endl;*/
		//读取数组信息
	//	cout << "Here's my achievements:" << endl;
		//cout << root["ch"].size();
		for (unsigned int i = 0; i < root["ch"].size(); i++)
		{
			string t = root["ch"][i]["type"].asString();
			string guanjianzi = root["ch"][i]["value"].asString();
			//cout << ach << endl;
			if (t == "1")
			{
				cout << '\"';
				for (;i < root["ch"].size(); i++) 
				{
					string t = root["ch"][i]["type"].asString();
					string guanjianzi = root["ch"][i]["value"].asString();
					//cout << guanjianzi;
					if (t == "5" || t == "6") 
					{
						cout << "\" -> ";
						break;
					}
					if (guanjianzi == "=") 
					{
						cout << " is";
					}
					else
					cout << " "<<guanjianzi;
				}
			}
			else if (t == "2")
			{
				//int temp = i;
				//for (;i < root["ch"].size(); i++)
				//{
				//	string t = root["ch"][i]["type"].asString();
				//	string guanjianzi = root["ch"][i]["value"].asString();
				//	cout << guanjianzi;
				//	//if (guanjianzi == "[") { break; }

				//	if (t == "5" || t == "6" && guanjianzi != "[" && guanjianzi != "]")
				//		cout <<';'<< endl;
				//		break;
				//}
				//i = temp;
				cout << '\"';
				for (;i < root["ch"].size(); i++)
				{
					string t = root["ch"][i]["type"].asString();
					string guanjianzi = root["ch"][i]["value"].asString();
					//cout << guanjianzi;
					if (t == "5" || t == "6")
					{
						cout << "\" -> ";
						break;
					}
					if (guanjianzi == "=")
					{
						cout << " is";
					}
					else
						cout << " " << guanjianzi;
				}
			}
			//else if (t == "3")
				//cout << guanjianzi << ';' << endl << guanjianzi << " -> ";
			//else if (t == "4")
				//cout << guanjianzi << ';' << endl << guanjianzi << " -> ";
			/*else if (t == "5")
				cout << guanjianzi << "->";
			else if (t == "6")
				cout << guanjianzi << "->";*/
			else if (t == "7"||t=="8") 
			{
				if (guanjianzi == "if") 
				{
					cout << "\"if";
					i++;
					for (;i < root["ch"].size(); i++)
					{
						string t = root["ch"][i]["type"].asString();
						string guanjianzi = root["ch"][i]["value"].asString();
						//cout << guanjianzi;
						if (guanjianzi==")")
						{
							cout <<guanjianzi<< "\" -> if -> ";
							break;
						}
						else
							cout << " " << guanjianzi;
					}
					/*if (guanjianzi == "else") 
					{
						cout << "if -> else" << endl;
					}*/
					

				}
				else if (guanjianzi == "else")
				{
					cout << "if_end; if_end ->";
					for (;i < root["ch"].size(); i++)
					{
						string t = root["ch"][i]["type"].asString();
						string guanjianzi = root["ch"][i]["value"].asString();
						//cout << guanjianzi;
						if (guanjianzi == ";")
						{
							//cout << guanjianzi << "\" -> ";
							break;
						}
						/*else
							cout << " " << guanjianzi;*/
					}
					i++;
					//cout << "if -> else;" << endl;
				}
				else if (guanjianzi == "for")
				{
					cout << "\"for";
					i++;
					for (;i < root["ch"].size(); i++)
					{
						string t = root["ch"][i]["type"].asString();
						string guanjianzi = root["ch"][i]["value"].asString();
						//cout << guanjianzi;
						if (guanjianzi == ")")
						{
							cout << guanjianzi << "\" -> for -> ";
							break;
						}
						else
							cout << " " << guanjianzi;
					}
				}
				else cout << guanjianzi << ';' << endl << guanjianzi << " -> ";
			}
			else if (t == "8"||t=="7") 
{
			 if (guanjianzi == "while")
			{
				cout << "\"while";
				i++;
				for (;i < root["ch"].size(); i++)
				{
					string t = root["ch"][i]["type"].asString();
					string guanjianzi = root["ch"][i]["value"].asString();
					//cout << guanjianzi;
					if (guanjianzi == ")")
					{
						cout << guanjianzi << "\" -> ";
						break;
					}
					else
						cout << " " << guanjianzi;
				}
			}
			cout << guanjianzi << ';' << endl << guanjianzi << " -> ";
			}
			else if (t == "9")
				cout << guanjianzi << ';' << endl << guanjianzi << " -> ";
		}
		cout << endl;
		for (int j=0;j < root["ch"].size(); j++)
		{
			string t = root["ch"][j]["type"].asString();
			string guanjianzi = root["ch"][j]["value"].asString();
			if (guanjianzi == "else")
			{
				cout << "if -> else;"<<endl;
				cout << "else";
				j++;
				for (;j < root["ch"].size(); j++)
				{
					string t = root["ch"][j]["type"].asString();
					string guanjianzi = root["ch"][j]["value"].asString();
					if (guanjianzi == ";")
					{
						cout << ";";
						break;
					}
					cout << " -> " << guanjianzi/*<<"-> if_end"*/;
					
					
				}
				cout << endl << root["ch"][--j]["value"].asString() << " -> ";
				j++;
				for (;j < root["ch"].size(); j++)
				{
					string t = root["ch"][j]["type"].asString();
					string guanjianzi = root["ch"][j]["value"].asString();
					if (t != "3" && t != "5" && t != "6")
					{
						cout <<"if_end -> "<< guanjianzi <<";"<< endl;
						break;
					}
				
				}
			}


		}
		/*for (int k = 0;k < root["ch"].size(); k++)
		{
			string t = root["ch"][k]["type"].asString();
			string guanjianzi = root["ch"][k]["value"].asString();
			if (guanjianzi == "for")
			{
				for (;k < root["ch"].size(); k++)
				{
					string t = root["ch"][k]["type"].asString();
					string guanjianzi = root["ch"][k]["value"].asString();
					if (guanjianzi == "}")
					{
						k--;
						cout << root["ch"][--k]["value"].asString()<<" -> for;"<<endl;
						break;
					}
				}
			}
		}*/
		for (int k = 0;k < root["ch"].size(); k++)
		{
			string t = root["ch"][k]["type"].asString();
			string guanjianzi = root["ch"][k]["value"].asString();
			if (guanjianzi == "for")
			{
				for (;k < root["ch"].size(); k++)
				{
					string t = root["ch"][k]["type"].asString();
					string guanjianzi = root["ch"][k]["value"].asString();
					if (guanjianzi == "}")
					{
						k--;
						k--;
						for (;k < root["ch"].size(); k--)
						{
							string t = root["ch"][k]["type"].asString();
							string guanjianzi = root["ch"][k]["value"].asString();
							if (guanjianzi == ";" || guanjianzi == "{")
							{
								break;
							}
						}
						k++;
						string t = root["ch"][k]["type"].asString();
						string guanjianzi = root["ch"][k]["value"].asString();
						//cout << "\"";
						if (t == "2")
						{
							cout << "\"";
							for (;k < root["ch"].size(); k++)
							{
								string t = root["ch"][k]["type"].asString();
								string guanjianzi = root["ch"][k]["value"].asString();
								//cout << " "<<guanjianzi;
								if (guanjianzi == ";")
								{
									break;
								}
								cout << " " << guanjianzi;
							}
							cout << "\"";
						}
						if (t == "7" || t == "8") 
						{
							for (;k < root["ch"].size(); k++)
							{
								string t = root["ch"][k]["type"].asString();
								string guanjianzi = root["ch"][k]["value"].asString();
								if (guanjianzi == ";")
								{
									break;
								}
								cout << " " << guanjianzi;
								//cout << guanjianzi;

							}
						}
						cout << " -> for;" << endl;
						break;
					}
				}
			}
		}
		for (int l = 0;l < root["ch"].size(); l++)
		{
			string t = root["ch"][l]["type"].asString();
			string guanjianzi = root["ch"][l]["value"].asString();
			if (guanjianzi == "while")
			{
				for (;l < root["ch"].size(); l++)
				{
					string t = root["ch"][l]["type"].asString();
					string guanjianzi = root["ch"][l]["value"].asString();
					if (guanjianzi == "}")
					{
						l--;
						l--;
						for (;l < root["ch"].size(); l--)
						{
							string t = root["ch"][l]["type"].asString();
							string guanjianzi = root["ch"][l]["value"].asString();
							if (guanjianzi == ";"||guanjianzi=="{") 
							{
								break;
							}
						}
						l++;
						string t = root["ch"][l]["type"].asString();
						string guanjianzi = root["ch"][l]["value"].asString();
						if (t == "2")
						{
							cout << "\"";
							for (;l < root["ch"].size(); l++)
							{
								string t = root["ch"][l]["type"].asString();
								string guanjianzi = root["ch"][l]["value"].asString();
								//cout << " "<<guanjianzi;
								if (guanjianzi == ";")
								{
									break;
								}
								cout << " " << guanjianzi;
							}
							cout << "\"" << endl;
						}
						if (t == "7" || t == "8")
						{
							for (;l < root["ch"].size(); l++)
							{
								string t = root["ch"][l]["type"].asString();
								string guanjianzi = root["ch"][l]["value"].asString();
								if (guanjianzi == ";")
								{
									break;
								}
								cout << " " << guanjianzi;
								//cout << guanjianzi;

							}
						}
						cout << " -> while;" << endl;
						break;
					}
				}
			}
		}
		cout << endl;
		//cout << "Reading Complete!" << endl;
	}
	else
	{
		cout << "parse error\n" << endl;
	}
	in.close();
}
