#include "TextIndexFile.h"

TextIndexFile::TextIndexFile(string indexFileName, string recordFileName, bool(*compare)(IndexElement a, IndexElement b)) {
	mRecordFile = new RecordFile(new MetaLengthBuffer(recordFileName));
	mTextIndexBuffer = new TextIndexBuffer(indexFileName, mIndexVector);

	mTextIndexBuffer->UnPack();
	mFuncCompare = compare;
}

TextIndexFile::~TextIndexFile() {
	mTextIndexBuffer->Pack("");
	delete(mTextIndexBuffer);
	delete(mRecordFile);
}

void TextIndexFile::PrintIndex() {
	cout << "SYSTEM: Print Index" << endl;
	if (mIndexVector.size() == 0) {
		cout << "---- no data ----" << endl;
	}
	for (int i = 0; i < mIndexVector.size(); i++) {
		cout << "    Index: " << i + 1 << ",\tKey : " << mIndexVector[i].field << ",\tDescriptor absolute address: " << mIndexVector[i].addr << endl;
	}
}

bool TextIndexFile::Read(recType& record, string key) {
	for (int i = 0; i < mIndexVector.size(); i++) {
		if (key == mIndexVector[i].field) {
			if (static_cast<int>(mRecordFile->Read(record, mIndexVector[i].addr)) == -1) {
				return false;
			}
			
			return true;
		}
	}
	cout << "SYSTEM: no result for search" << endl;
	return false;
}


void TextIndexFile::Remove(string key) {
	for (int i = 0; i < mIndexVector.size(); i++) {
		if (key == mIndexVector[i].field) {
			mRecordFile->Remove(mIndexVector[i].addr);

			// caution!! use erase in stl vector
			mIndexVector.erase(mIndexVector.begin() + i);

			sort(mIndexVector.begin(), mIndexVector.end(), mFuncCompare);
			// you modified index, write index
			mTextIndexBuffer->Pack("");
			return;
		}
	}
	cout << "SYSTEM: no result for remove index" << endl;
}

void TextIndexFile::Append(recType& record, string key) {
	IndexElement element;
	element.addr = mRecordFile->Append(record);
	element.field = key;

	mIndexVector.push_back(element);

	sort(mIndexVector.begin(), mIndexVector.end(), mFuncCompare);
	mTextIndexBuffer->Pack("");
}