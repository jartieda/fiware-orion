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
#include "logMsg/logMsg.h"

#include "serviceRoutines/postRegisterContext.h"
#include "serviceRoutines/getContextEntityTypes.h"
#include "serviceRoutines/badVerbGetPostOnly.h"
#include "serviceRoutines/badRequest.h"
#include "rest/RestService.h"

#include "unittest.h"



/* ****************************************************************************
*
* rs - 
*/
static RestService rs[] = 
{
  { "POST", RegisterContext,    2, { "ngsi9", "registerContext"         }, "", postRegisterContext   },
  { "GET",  ContextEntityTypes, 3, { "ngsi9", "contextEntityTypes", "*" }, "", getContextEntityTypes },
  { "*",    ContextEntityTypes, 3, { "ngsi9", "contextEntityTypes", "*" }, "", badVerbGetPostOnly    },
  { "*",    InvalidRequest,     0, { "*", "*", "*", "*", "*", "*"       }, "", badRequest            },
  { "",     InvalidRequest,     0, {                                    }, "", NULL                  }
};



/* ****************************************************************************
*
* nothingFound - 
*/
TEST(getContextEntityTypes, nothingFound)
{
  ConnectionInfo ci("/ngsi9/contextEntityTypes/TYPE_123",  "GET", "1.1");
  const char*    outfile = "ngsi9.discoverContextAvailabilityResponse.notFound.valid.xml";
  std::string    out;

  utInit();

  ci.outFormat = XML;
  out          = restService(&ci, rs);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile)) << "Error getting test data from '" << outfile << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  utExit();
}



/* ****************************************************************************
*
* somethingFound - 
*/
TEST(getContextEntityTypes, somethingFound)
{
  ConnectionInfo ci1("/ngsi9/registerContext",          "POST", "1.1");
  ConnectionInfo ci2("/ngsi9/contextEntityTypes/Room",  "GET", "1.1");
  const char*    infile    = "ngsi9.registerContextRequest.ok.valid.xml";
  const char*    outfile1  = "ngsi9.registerContext.getContextEntityTypes.middle.xml";
  const char*    outfile2  = "ngsi9.discoverContextAvailabilityResponse.getContextEntityTypes.valid.xml";
  std::string    out;

  utInit();

  // Avoid forwarding of messages
  extern int fwdPort;
  int saved = fwdPort;


  //
  // 1. Register entities so we have something to find:
  //    - entityId type="Room" isPattern="false", ConferenceRoom
  //    - entityId type="Room" isPattern="false", OfficeRoom
  //
  EXPECT_EQ("OK", testDataFromFile(testBuf, sizeof(testBuf), infile)) << "Error getting test data from '" << infile << "'";

  ci1.outFormat    = XML;
  ci1.inFormat     = XML;
  ci1.payload      = testBuf;
  ci1.payloadSize  = strlen(testBuf);
  out              = restService(&ci1, rs);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile1)) << "Error getting test data from '" << outfile1 << "'";

  char* outStart  = (char*) out.c_str();

  // Remove last char in expectedBuf
  expectedBuf[strlen(expectedBuf) - 1] = 0;

  // Shorten 'out' to besame length as expectedBuf
  outStart[strlen(expectedBuf)]    = 0;
  EXPECT_STREQ(expectedBuf, out.c_str());


  //
  // Now discover
  //
  ci2.outFormat = XML;
  out           = restService(&ci2, rs);

  EXPECT_EQ("OK", testDataFromFile(expectedBuf, sizeof(expectedBuf), outfile2)) << "Error getting test data from '" << outfile2 << "'";
  EXPECT_STREQ(expectedBuf, out.c_str());

  // Putting old value back
  fwdPort = saved;

  utExit();
}
