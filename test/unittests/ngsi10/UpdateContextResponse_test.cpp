/*
*
* Copyright 2013 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include "gtest/gtest.h"

#include "ngsi10/UpdateContextResponse.h"

#include "unittest.h"



/* ****************************************************************************
*
* constructors - 
*/
TEST(UpdateContextResponse, constructors)
{
  UpdateContextResponse  ucr1;
  ErrorCode              ec(SccBadRequest, "RP", "D");
  UpdateContextResponse  ucr2(ec);
  std::string            rendered;
  std::string            expected1 = "<updateContextResponse>\n  <errorCode>\n    <code>404</code>\n    <reasonPhrase>No context element found</reasonPhrase>\n  </errorCode>\n</updateContextResponse>\n";
  std::string            expected2 = "<updateContextResponse>\n  <errorCode>\n    <code>400</code>\n    <reasonPhrase>RP</reasonPhrase>\n    <details>D</details>\n  </errorCode>\n</updateContextResponse>\n";

  utInit();

  rendered = ucr1.render(UpdateContext, XML, "");
  EXPECT_STREQ(expected1.c_str(), rendered.c_str());

  rendered = ucr2.render(UpdateContext, XML, "");
  EXPECT_STREQ(expected2.c_str(), rendered.c_str());

  utExit();
}



/* ****************************************************************************
*
* jsonRender - 
*/
TEST(UpdateContextResponse, jsonRender)
{
  const char*              filename1  = "ngsi10.updateContextResponse.jsonRender1.valid.json";
  const char*              filename2  = "ngsi10.updateContextResponse.jsonRender2.valid.json";
  const char*              filename3  = "ngsi10.updateContextResponse.jsonRender3.valid.json";
  const char*              filename4  = "ngsi10.updateContextResponse.jsonRender4.valid.json";
  const char*              filename5  = "ngsi10.updateContextResponse.jsonRender5.valid.json";
  const char*              filename6  = "ngsi10.updateContextResponse.jsonRender6.valid.json";
  const char*              filename7  = "ngsi10.updateContextResponse.jsonRender7.valid.json";
  const char*              filename8  = "ngsi10.updateContextResponse.jsonRender8.valid.json";
  const char*              filename9  = "ngsi10.updateContextResponse.jsonRender9.valid.json";
  const char*              filename10 = "ngsi10.updateContextResponse.jsonRender10.valid.json";
  const char*              filename11 = "ngsi10.updateContextResponse.jsonRender11.valid.json";
  const char*              filename12 = "ngsi10.updateContextResponse.jsonRender12.valid.json";
  const char*              filename13 = "ngsi10.updateContextResponse.jsonRender13.valid.json";

  UpdateContextResponse*   ucrP;
  ContextElementResponse*  cerP;
  Metadata*                mdP;
  ContextAttribute*        caP;
  std::string              rendered;

  // Preparations
  utInit();
  ucrP = new UpdateContextResponse();

  // Test 01. UpdateContextResponse::errorCode OK and contextElementResponseVector filled id (no details)
  // Test 02. UpdateContextResponse::errorCode NOT OK and contextElementResponseVector filled id (with details)
  // Test 03. ContextElement: +entityId -attributeDomainName -contextAttributeVector -domainMetadataVector
  // Test 04. ContextElement: +entityId -attributeDomainName -contextAttributeVector +domainMetadataVector
  // Test 05. ContextElement: +entityId -attributeDomainName +contextAttributeVector -domainMetadataVector
  // Test 06. ContextElement: +entityId -attributeDomainName +contextAttributeVector +domainMetadataVector
  // Test 07. ContextElement: +entityId +attributeDomainName -contextAttributeVector -domainMetadataVector
  // Test 08. ContextElement: +entityId +attributeDomainName -contextAttributeVector +domainMetadataVector
  // Test 09. ContextElement: +entityId +attributeDomainName +contextAttributeVector -domainMetadataVector
  // Test 10. ContextElement: +entityId +attributeDomainName +contextAttributeVector +domainMetadataVector
  // Test 11. ContextElement: contextAttributeVector of two attributes
  // Test 12. ContextElement: domainMetadataVector of two metadatas
  // Test 13. UpdateContextResponse::contextElementResponseVector of TWO responses


  // Test 01. UpdateContextResponse::errorCode OK and contextElementResponseVector filled id (no details)
  ucrP->errorCode.fill(SccOk, "OK");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename1)) << "Error getting test data from '" << filename1 << "'";
  rendered = ucrP->render(UpdateContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 02. UpdateContextResponse::errorCode NOT OK and contextElementResponseVector filled id (with details)
  ucrP->errorCode.fill(SccBadRequest, "Bad Request", "no details");
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename2)) << "Error getting test data from '" << filename2 << "'";
  rendered = ucrP->render(UpdateContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());
  ucrP->errorCode.fill(SccOk, "OK"); // Cleanup



  // Test 03. ContextElement: +entityId -attributeDomainName -contextAttributeVector -domainMetadataVector
  cerP = new ContextElementResponse();

  cerP->contextElement.entityId.fill("E01", "EType", "false");
  cerP->statusCode.fill(SccOk, "OK", "");
  ucrP->contextElementResponseVector.push_back(cerP);
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename3)) << "Error getting test data from '" << filename3 << "'";
  rendered = ucrP->render(UpdateContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 04. ContextElement: +entityId -attributeDomainName -contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md4", "string", "FIN4");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename4)) << "Error getting test data from '" << filename4 << "'";
  rendered = ucrP->render(UpdateContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 05. ContextElement: +entityId -attributeDomainName +contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  caP = new ContextAttribute("ca5", "string", "context attribute 5");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename5)) << "Error getting test data from '" << filename5 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  

  // Test 06. ContextElement: +entityId -attributeDomainName +contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md6", "string", "FIN6");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename6)) << "Error getting test data from '" << filename6 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());
  

  // Test 07. ContextElement: +entityId +attributeDomainName -contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  cerP->contextElement.contextAttributeVector.release();
  cerP->contextElement.attributeDomainName.set("AttrDomain");

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename7)) << "Error getting test data from '" << filename7 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 08. ContextElement: +entityId +attributeDomainName -contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md8", "string", "FIN8");
  cerP->contextElement.domainMetadataVector.push_back(mdP);
  
  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename8)) << "Error getting test data from '" << filename8 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 09. ContextElement: +entityId +attributeDomainName +contextAttributeVector -domainMetadataVector
  cerP->contextElement.domainMetadataVector.release();
  caP = new ContextAttribute("ca9", "string", "context attribute 9");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename9)) << "Error getting test data from '" << filename9 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 10. ContextElement: +entityId +attributeDomainName +contextAttributeVector +domainMetadataVector
  mdP = new Metadata("md10", "string", "FIN10");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename10)) << "Error getting test data from '" << filename10 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 11. ContextElement: contextAttributeVector of two attributes
  caP = new ContextAttribute("ca11", "string", "context attribute 11");
  cerP->contextElement.contextAttributeVector.push_back(caP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename11)) << "Error getting test data from '" << filename11 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 12. ContextElement: domainMetadataVector of two metadatas
  mdP = new Metadata("md12", "string", "FIN12");
  cerP->contextElement.domainMetadataVector.push_back(mdP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename12)) << "Error getting test data from '" << filename12 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());



  // Test 13. UpdateContextResponse::contextElementResponseVector of TWO responses
  cerP = new ContextElementResponse();

  cerP->contextElement.entityId.fill("E02", "EType", "false");
  cerP->statusCode.fill(SccOk, "OK");
  ucrP->contextElementResponseVector.push_back(cerP);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), filename13)) << "Error getting test data from '" << filename13 << "'";
  rendered = ucrP->render(QueryContext, JSON, "");
  EXPECT_STREQ(expectedBuf, rendered.c_str());

  utExit();
}
