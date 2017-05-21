#pragma once

/*
근본적으로 이 recaddr이 말이 안되는 이유가 있는데
삭제 가능한 레코드 버퍼를 1 2 3 4 이런 식으로 접근한다는 게 말이 안된다.
1 2 3 4 넣고  3 삭제했는데 거기에 다시 다른 레코드가 추가되서 공간이 남으면
1 2 3(추가) 4(avail list 여분) 5 로 기존 4번이었던 레코드가 5가 되어
절대적인 접근 Index가 보장되지 않는다.

그렇다고 이걸 실제 파일 디스크립터 값으로 하자니
버퍼 내용 모르게 하겟다고 만든 이 클래스가
버퍼가 어떤식으로 동작하는지도 모르는데 디스크립터 값이라니 말도 안된다.

심지어 Append는 recaddr 쓰지도 않는데 파라미터로 받고있음.
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
