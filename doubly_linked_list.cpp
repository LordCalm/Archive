#include <iostream>
#include <Windows.h>
#include "DoublyLinkedList.h"
#include <fstream>
#pragma warning(disable:4996)

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

//const int size_string = 128;

size_t node::Checksum()
{
	#ifndef FAST_LIST
	if (_next != NULL && _prev != NULL)
	{
		size_t a = (size_t)_next, b = (size_t)_prev;
		return ((a * b) / (a + b)) + 21442;
	}
	else if (_next != NULL)
	{
		size_t c = (size_t)_next;
		return ((c * c) / (c + 15616)) + 21442;
	}
	else if (_prev != NULL)
	{
		size_t d = (size_t)_prev;
		return ((d * d) / (d + 15616)) + 21442;
	}
	#endif
	return 0;
}
void node::OK()
{
	#ifndef FAST_LIST
	if (_can1 != CAN || _can2 != CAN || Checksum() != _checksum)
	{
		MessageBox::Show("?????? ???? ??????? ??? ????????", "??????");
	}
	#endif
	return;
}


void list::ListOK()
{
	if (_head != NULL && _tail != NULL)
		return;
	MessageBox::Show("?????? ??????:\n?????? ?? ??????", "??????");
}
void list::PrintList()
{
	link cur = _head;
	while (cur)
	{
		if (cur != NULL) cur->OK();
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << "\n";
}
void list::InsertAfter(int index, type data)
{
	ListOK();
	if (_head->_data)
	{
		if (0 < index && index <= _size)
		{
			_size++;
			if (_head != NULL) _head->OK();
			link cur = _head;
			for (int i = 1; i < index; i++)
			{
				cur = cur->_next;
			}
			if (cur != NULL) cur->OK();
			if (cur->_next != NULL) (cur->_next)->OK();
			/*
			#ifdef LIST_OF_STRINGS
			link el = new node(NULL);
			el->_data = new char[size_string];
			snprintf(el->_data, strlen(data) + sizeof("\0"), data);
			#else
			link el = new node(data);
			#endif
			*/
			link el = new node(data);
			el->_next = cur->_next;
			el->_prev = cur;
			cur->_next = el;
			if (el->_next != NULL)
			{
				(el->_next)->_prev = el;

				#ifndef FAST_LIST
				el->_next->_checksum = el->_next->Checksum();
				#endif
			}

			#ifndef FAST_LIST
			el->_checksum = el->Checksum();
			el->_prev->_checksum = el->_prev->Checksum();
			#endif

			if (el != NULL) el->OK();
			if (_tail->_next)
			{
				_tail = _tail->_next;
			} 
			return;
		}
	}
	else
	{
		if (0 <= index)
		{
			_size++;
			link el = new node(data);
			el->_data = data;

			#ifndef FAST_LIST
			el->_checksum = el->Checksum();
			#endif

			_head = el;
			_tail = el;
			return;
		}
	}
	MessageBox::Show("?????? ?????????? ??????", "??????");
}
void list::InsertBefore(int index, type data)
{
	ListOK();
	if (index == 1)
	{
		_size++;
		if (_head != NULL) _head->OK();
		link cur = _head;
		link el = new node(data);
		el->_data = data;
		el->_next = cur;
		cur->_prev = el;
		_head = el;

		#ifndef FAST_LIST
		cur->_checksum = cur->Checksum();
		el->_checksum = el->Checksum();
		#endif

		if (el != NULL) el->OK();
		return;
	}
	else if (1 < index && index <= _size)
	{
		_size++;
		if (_head != NULL) _head->OK();
		link cur = _head;
		for (int i = 1; i < index; i++)
		{
			cur = cur->_next;
		}
		if (cur != NULL) cur->OK();
		if (cur->_prev != NULL) (cur->_prev)->OK();
		link el = new node(data);
		el->_data = data;
		el->_next = cur;
		el->_prev = cur->_prev;
		cur->_prev->_next = el;
		cur->_prev = el;

		#ifndef FAST_LIST
		cur->_checksum = cur->Checksum();
		cur->_prev->_checksum = cur->_prev->Checksum();
		el->_checksum = el->Checksum();
		#endif

		if (el != NULL) el->OK();
		return;
	}
	MessageBox::Show("?????? ?????????? ??????", "??????");
}
void list::ArrayToList(type *Array, int size)
{
	if (Array != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			InsertAfter(i, Array[i]);
		}
	}
	else
	{
		MessageBox::Show("?????? ?? ???????? ?????????", "??????");
	}
}
void list::Delete(int index)
{
	ListOK();
	if (0 < index && index <= _size)
	{
		_size--;
		if (_head != NULL) _head->OK();
		link cur = _head;
		int i = 1;
		while (i < index)
		{
			cur = cur->_next;
			i++;
		}
		if (cur != NULL) cur->OK();
		if (index != 1)
		{
			if (cur->_prev != NULL) {
				(cur->_prev)->OK();
				cur->_prev->_next = cur->_next;
			}
			
			if (cur->_next != NULL) {
				(cur->_next)->OK();
				cur->_next->_prev = cur->_prev;
			}

			#ifndef FAST_LIST
			cur->_prev->_checksum = cur->_prev->Checksum();
			#endif
			delete cur;
		}
		else
		{
			if (cur->_next != NULL) {
				(cur->_next)->OK();
				_head = cur->_next;

				#ifndef FAST_LIST
				_head->_checksum = _head->Checksum();
				#endif

				cur->_next->_prev = cur->_prev; //NULL

				#ifndef FAST_LIST
				cur->_next->_checksum = cur->_next->Checksum();
				#endif
				delete cur;
			}
			else {
				delete cur;
				_head = _tail = new node();
			}
		}
		MessageBox::Show("?????? ???? ??????? ???????", "???????");
		return;
	}
	MessageBox::Show("?????? ???????? ??????", "??????");
}
int strcmpare(char *str1, char *str2)
{
	int i = 0;
	while (*(str1 + i) != NULL || *(str2 + i) != NULL)
	{
		if (*(str1 + i) != *(str2 + i)) return 0;
		i++;
	}
	if (*(str1 + i) == NULL && *(str2 + i) == NULL)
		return 1;
	else
		return 0;
}
int list::FindString(type data)
{
	link cur = _head;
	int i = 1;
	while (cur != NULL)
	{
		if (cur->_data == NULL)
			return 0;
		//strstr(cur->_data, data) != NULL
		//strcmpare(data, cur->_data) != 0
		if (strstr(cur->_data, data) != NULL)
		{
			return i;
		}
		cur = cur->_next;
		i++;
	}
	return 0;
}
char* list::FindSubString(type data)
{
	link cur = _head;
	int i = 1;
	char buf[10] = {};
	string result = "";
	strncpy(buf, cur->_data, 10);
	while (cur != NULL)
	{
		if (cur->_data == NULL)
			return 0;
		if (strcmpare(data, buf) == 0)
		{
			result.append(cur->_data);
			result.append(" ");
		}
		cur = cur->_next;
		i++;
	}
	if (result != "") {
		char* cstr = new char[result.length() + 1];
		strcpy(cstr, result.c_str());
		return cstr;
		delete[] cstr;
	}
	char* massage = new char[strlen("?????? ? ???????? ???????????") + 1];
	strcpy(massage, "?????? ? ???????? ???????????");
	return massage;
}
link list::FindPtr(type data)
{
	link cur = _head;
	while (cur->_data != data)
	{
		cur = cur->_next;
	}
	return cur;
}
int list::FindIndex(type data)
{
	link cur = _head;
	int i = 1;
	while (cur != NULL)
	{
		if (cur->_data == NULL)
			return 0;
		//cur->_data == data
		if (strstr(cur->_data, data) != NULL)
		{
			return i;
		}
		cur = cur->_next;
		i++;
	}
	return 0;
	
}
void list::Swap(link ptr1, link ptr2)
{
	type buf = ptr1->_data;
	ptr1->_data = ptr2->_data;
	ptr2->_data = buf;
}
void list::BubbleSort()
{
	link cur = _head;
	int check = 1;
	while (check != 0)
	{
		int check1 = 0;
		while (cur->_next != NULL)
		{
			if (cur->_data > (cur->_next)->_data)
			{
				Swap(cur, cur->_next);
				check1++;
			}
			cur = cur->_next;
		}
		if (check1 == 0) check = 0;
		cur = _head;
	}
	_head = cur;
	MessageBox::Show("?????? ??????????", "??????");
}


ofstream& operator<<(ofstream& out, const node& data)
{
	out << data._can1 << '&' << data._data << '&' << data._checksum << '&' << data._can2 << '&' << '\n';

	return out;
}

ifstream& operator>>(ifstream& in, node& data)
{
	//string str = "";

	//in >> data._can1;
	//in.get();
	//in >> str;

	//char* cstr = new char[str.length() + 1];

	//strcpy(cstr, str.c_str());
	//data._data = cstr;
	//in.get(); // ??????? ???? ??????, ? ????? ?????? ??????
	//in >> data._checksum;
	//data._checksum = 0;
	//in.get();
	//in >> data._can2;
	//in.get(); // ???????? ?????? ????? ??????
	char buf[50] = {};
	in.getline(buf, 50, '&');
	data._can1 = atoi(buf);
	in.getline(buf, 50, '&');
	string str = buf;
	char* cstr = new char[str.length() + 1];
	strcpy(cstr, str.c_str());
	data._data = cstr;
	in.getline(buf, 50, '&');
	data._checksum = 0;
	in.getline(buf, 50, '&');
	data._can2 = atoi(buf);
	return in;
}