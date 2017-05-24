[ 2017. 05. 23 ]
[ ���ϱ��� ���� 3 	201310923 �̻�� ]

-------------------------------------------------------------------------------------------------------------------------------

TextIndexFile.h

This class is used to store data using indexes.
The buffer is a variable field buffer using metadata, and the index is implemented by the IndexElement class.
The details of the IndexElement class are as follows :

	class IndexElement {
	public:
		streampos addr;
		string field;
	}

	- field is the key value of the index to be compared,
	- addr is the absolute descriptor value of the actual record.

< How to use >

	- Initialize the constructor.

		TextIndexFile(string indexFileName, string recordFileName, bool (*compare)(IndexElement a, IndexElement b))

		indexFileName   : The path where Index File
		recordFileName  : The path where the actual record is stored
		compare		: (Function Pointer) to compare key to be stored

		* File must exist in path

	- Method.

		bool Read(recType& record, string key);
			- Store the read record in the record passed as parameter.
			  Returns true if read was successful.

		void Remove(string key);
			- Find and remove records with the same key.

		void Append(recType& record, string key);
			- Store record and key.

		void PrintIndex();
			- Print all existing indexes.

---------------------------------------------------------------------------------------------------------------------------------

recType.h

class recType {
public:
	virtual void Pack(FileStream* f) = 0;
	virtual void UnPack(FileStream* f) = 0;
};

	- Pack 	  : Call 'f-> Pack (string field);' in the order that you want to put in at the buffer.
	- UnPack  : Call 'f-> UnPack ();' in the order you want to import in the buffer.

---------------------------------------------------------------------------------------------------------------------------------

Test Program

	- ���α׷��� ó�� �Ѹ� ���� record ���� ���¸� ���� ����Ѵ�.
	- field 3��¥�� Person class �� ���Ƿ� ����� ���.
	- compare �Լ��� key�� �� �ʵ��� ù ���ڸ� ���� ������������ �����Ѵ�.
	- ��� 4����
		1) 'append'	record �߰� ���, �� field�� ������ �Է¹ް� ������ Ű�� ���� �Է��ϸ� record�� �߰��ȴ�. ���� ������ ������ �� �����Ѵ�.
		2) 'remove'	record ���� ���, key�� �Է¹ް� key�� ������ ������ �����ϸ� �� record�� ����, ������ ������ �� �����Ѵ�.
		3) 'read'	record �б� ���, key�� �Է¹ް� key�� ������ ������ �����ϸ� �� record ������ ����Ѵ�. ����Լ��� Person ��ü�� ������ �ִ�.
		4) 'printindex'	���� ��� ���, ���� �����ϴ� record ������ ����Ѵ�.

	- ���� ����Ǵ� record ������ ����� �ּ� meta data�� sizeof(int)*2 ��.
	  �̹� record�� ������ �ڸ��� �̰ͺ��� ���� �뷮�� ����� record�� �߰��� ��� ������ �� ������ ������� �� �� ���̹Ƿ� append�� �� ��� ���� �˻��� ���� ���� ���� �߰��Ѵ�.

