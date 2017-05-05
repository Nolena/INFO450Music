// Info450 Assignment 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;

class Music 
	{
		string song;
		Music *next;

		public:
			Music() {}
			Music(string s) 
				{
					song = s;
					next = NULL;
				}
			friend class MusicList;
	};

class MusicList 
	{
		Music *head;
		Music *tail;

		public:
			MusicList() 
				{
					head = NULL;
					tail = NULL;
				}
			void AddSongToEnd(Music *ptr)
				{
					if (head == NULL)
					{
						head = ptr;
						tail = ptr;
					}
					else
					{
						tail->next = ptr;
						tail = ptr;
					}
				}
			void AddSongToHead(Music *ptr) 
				{
					if (head == NULL)
						{
							head = ptr;
							tail = ptr;
						}
					else
						{
							ptr->next = head;
							head = ptr;
						}
				}
			int InsertAfter(Music *newnode, string i) //Extra Credit
				{
					Music *ptr;
					ptr = head;
					while (ptr != NULL)
						{
							if (ptr-> song == i)
								{
									newnode->next = ptr->next;
									ptr->next = newnode;
									if (tail == ptr)
										tail = newnode;
									return 0;
								}
							ptr = ptr->next;
						}
					return -1;
				}
			int RemoveNode(string i) 
				{
					Music *ptr = head;
					if (ptr == NULL)
						return -1;
					if (head->song == i)
						{
							if (head == tail)
								{
									head = NULL;
									tail = NULL;
								}
							else
								head = head->next;
							delete ptr;
							return 0;
						}
					while (ptr != NULL)
						{
							if (ptr->next && (ptr->next)->song == i)
								{
									if (tail == ptr->next)
										tail = ptr;
									Music *tbd = ptr->next;
									ptr->next = (ptr->next)->next;
									delete tbd;
									return 0;
								}
							ptr = ptr->next;
						}
					return -1;
				}

			void ShowMusicList() 
				{
					Music *ptr;
					ptr = head;
					char answer;
					cout << "***************************" << endl;
					cout << "**** Andrew's Playlist ****" << endl;
					cout << "============================" << endl;
					if (ptr == NULL)
						{
							cout << "list is empty" << endl;
							return;
						}
					while (ptr != NULL) 
						{
							do
								{
									if (ptr == NULL)
										{
											ptr = head;
										}
									cout << "Next song: " << ptr->song << endl;
									cout << "---------------------------------------" << endl;
									cout << "(P)lay, (S)kip, (A)dd, (D)elete, (Q)uit" << endl;
									cout << "---------------------------------------" << endl;
									cin >> answer;
					
									if (answer == 'P' || answer == 'p')
										{
											cout << "Playing: " << ptr->song << endl;
											cout << "---------------------------------------" << endl;
											ptr = ptr->next;
										}
									else if (answer == 'S' || answer == 's')
										{
											int n;
											cout << "Enter the number of songs you want to skip: ";
											cin >> n;
											cout << "---------------------------------------" << endl;
											for (int i = 0; i < n; i++)
												{
													if (ptr == NULL)
														{
															ptr = head;
														}
													cout << "Skipping " << ptr->song << endl;
													ptr = ptr->next;
												}
											cout << "---------------------------------------" << endl;

										}
									else if (answer == 'A' || answer == 'a') //Extra Credit
										{
											cin.ignore();
											string songName;
											cout << "Enter the title of the new song: ";
											getline(cin, songName);
											InsertAfter(new Music(songName), ptr->song);
											cout << "Song added to playlist!" << endl;
											cout << "---------------------------------------" << endl;
										}
									else if (answer == 'D' || answer == 'd')
										{
											string remove = ptr->song;
											ptr = ptr->next;
											RemoveNode(remove);
											cout << "Song deleted from playlist!" << endl;
											cout << "---------------------------------------" << endl;
										}
									else if (answer == 'Q' || answer == 'q')
										{
											return;
										}
									else 
										{
											cout << "Invalid selection, please try again" << endl;
											cout << "---------------------------------------" << endl;
										}
								} while (answer != 'Q' || answer != 'q');
						}
				}
			Music *findSong(string i) 
				{
					Music *ptr;
					ptr = head;
					while (ptr != NULL)
						{
							if (ptr->song == i)
								{
									cout << "Song: " << endl;
									return ptr;
								}
							ptr = ptr->next;
						}
					cout << "Not found" << endl;
					return NULL;
				}
			int ReadMusicList(string filename)
				{
					int count = 0;
					string sname;
					ifstream infile(filename, ios::in);
					if (!infile)
						{
							cout << "File could not be opened for reading" << endl;
							return READERROR;
						}
					while (!infile.eof())
						{
							getline(infile, sname);
							if (!sname.empty())
								{
								if (count == 0)
									{
									Music *newnode = new Music(sname);
									count++;
									}

								AddSongToEnd(new Music(sname));
								count++;
								}
						}
					infile.close();
					return 0;
				}
			int SaveMusicList(string filename)
				{
					ofstream output(filename, ios::trunc);
					if (!output)
						{
							cout << "Could not write to file!" << endl;
							return WRITEERROR;
						}
					if (output)
						{
							Music *ptr;
							ptr = head;
							while (ptr != NULL)
								{
									output << ptr->song << endl;
									ptr = ptr->next;
								}
						}
					output.close();
					return 0;
				}
	};

int main()
	{
		string filename;
		MusicList *mylist = new MusicList();
		cout << "What is the full file path for your music library?" << endl;
		getline(cin, filename);
		mylist->ReadMusicList(filename);
		mylist->ShowMusicList();
		mylist->SaveMusicList(filename);
		return 0;
	}

