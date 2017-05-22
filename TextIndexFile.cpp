#include "TextIndexFile.h"

TextIndexFile::TextIndexFile(string indexFileName, string recordFileName) {
	

	mRecordFile = new RecordFile(new MetaLengthBuffer(recordFileName));
	mTextIndexBuffer = new TextIndexBuffer(indexFileName, mIndexVector);

	IndexElement e;
	e.addr = 322;
	e.field = "sdlkfsdf";
	//mIndexVector.push_back(e);
	//mIndexVector.push_back(e);
	//mTextIndexBuffer->Pack("");
	mTextIndexBuffer->UnPack();
	this->PrintIndex();
}

TextIndexFile::~TextIndexFile() {
	delete(mRecordFile);
	mTextIndexBuffer->Pack("");
	delete(mTextIndexBuffer);
}

void TextIndexFile::PrintIndex() {
	for (int i = 0; i < mIndexVector.size(); i++) {
		cout << mIndexVector[i].field << " " << mIndexVector[i].addr << endl;

	}
}
