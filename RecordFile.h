#pragma once

/*
�ٺ������� �� recaddr�� ���� �ȵǴ� ������ �ִµ�
���� ������ ���ڵ� ���۸� 1 2 3 4 �̷� ������ �����Ѵٴ� �� ���� �ȵȴ�.
1 2 3 4 �ְ�  3 �����ߴµ� �ű⿡ �ٽ� �ٸ� ���ڵ尡 �߰��Ǽ� ������ ������
1 2 3(�߰�) 4(avail list ����) 5 �� ���� 4���̾��� ���ڵ尡 5�� �Ǿ�
�������� ���� Index�� ������� �ʴ´�.

�׷��ٰ� �̰� ���� ���� ��ũ���� ������ ���ڴ�
���� ���� �𸣰� �ϰٴٰ� ���� �� Ŭ������
���۰� ������� �����ϴ����� �𸣴µ� ��ũ���� ���̶�� ���� �ȵȴ�.

������ Append�� recaddr ������ �ʴµ� �Ķ���ͷ� �ް�����.
*/

#ifndef __RECORDFILE__
#define __RECORDFILE__
#include "FileStream.h"
#include "recType.h"

class RecordFile {
private:
	FileStream* mBuffer;
public:
	RecordFile(FileStream* buffer);
	int Read(recType& record, int recaddr = -1);
	int Write(recType& record, int recaddr = -1);
	int Append(recType& record);
	int Remove(int recaddr = -1);
};

#endif // !__RECORDFILE__
