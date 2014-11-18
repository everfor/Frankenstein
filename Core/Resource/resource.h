#pragma once

class Resource
{
	public:
		Resource() : referenceCount(0) {};
		~Resource() {};
		int getRefCount() { return referenceCount; };
		void increaseRefCout() { ++referenceCount; };
		void decreaseRefCout() { --referenceCount; };
		bool hasNoReference() { return referenceCount <= 0; };
	private:
		int referenceCount;
};