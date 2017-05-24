[ 2017. 05. 23 ]
[ 파일구조 과제 3 	201310923 이상민 ]

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

	- 프로그램을 처음 켜면 현재 record 저장 상태를 전부 출력한다.
	- field 3개짜리 Person class 를 임의로 만들어 사용.
	- compare 함수는 key가 된 필드의 첫 글자를 비교해 오름차순으로 정렬한다.
	- 명령 4가지
		1) 'append'	record 추가 명령, 각 field를 순차로 입력받고 무엇을 키로 할지 입력하면 record가 추가된다. 이후 색인을 재정렬 및 저장한다.
		2) 'remove'	record 삭제 명령, key를 입력받고 key와 동일한 색인이 존재하면 그 record를 삭제, 색인을 재정렬 및 저장한다.
		3) 'read'	record 읽기 명령, key를 입력받고 key와 동일한 색인이 존재하면 그 record 정보를 출력한다. 출력함수는 Person 객체가 가지고 있다.
		4) 'printindex'	색인 출력 명령, 현재 존재하는 record 색인을 출력한다.

	- 실제 저장되는 record 파일은 저장시 최소 meta data가 sizeof(int)*2 다.
	  이미 record가 삭제된 자리에 이것보다 작은 용량을 남기고 record가 추가될 경우 영원히 이 공간은 사용하지 못 할 것이므로 append때 이 경우 따로 검사해 파일 제일 끝에 추가한다.

