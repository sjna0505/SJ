#include "searcheng.h"

// Place your function implementations for your derived
// WebPageSetCombiner classes here

using namespace std;



WebPageSet ANDWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{

    WebPageSet webpgs;
 
    for(set<WebPage*>::iterator itA = setA.begin(); itA != setA.end(); ++itA)
    {
    	//if the terms exists in both sets
    	set<WebPage*>::iterator itB = setB.find(*itA);
    	if(itB != setB.end())
    		webpgs.insert(*itA);
    }

    return webpgs;

}

WebPageSet ORWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{

	WebPageSet webpgs;

	//insert everything. if the key already exists, insert would do nothing
	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); ++it){
		webpgs.insert(*it);
	}

	for(set<WebPage*>::iterator it = setB.begin(); it != setB.end(); ++it){
		webpgs.insert(*it);
	}

	return webpgs;
}

WebPageSet DIFFWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{

	WebPageSet webpgs;

	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); ++it){
		
		//if you don't find the element of setA in setB
		if(setB.find(*it) == setB.end())
			webpgs.insert(*it);
	}

    return webpgs;

}

