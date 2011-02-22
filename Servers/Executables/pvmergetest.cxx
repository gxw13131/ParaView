/*=========================================================================

Program:   ParaView
Module:    pvtest.cxx

Copyright (c) Kitware, Inc.
All rights reserved.
See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "paraview.h"
#include "vtkInitializationHelper.h"
#include "vtkProcessModule.h"
#include "vtkPVDataInformation.h"
#include "vtkPVFileInformation.h"
#include "vtkPVServerOptions.h"
#include "vtkPVXMLElement.h"
#include "vtkSMMessage.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMProxyDefinitionManager.h"
#include "vtkSMProxyManager.h"
#include "vtkSMRenderViewProxy.h"
#include "vtkSMSessionClient.h"
#include "vtkSMSession.h"
#include "vtkSMSourceProxy.h"

//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  int return_value = EXIT_SUCCESS;

  vtkPVServerOptions* options = vtkPVServerOptions::New();
  vtkInitializationHelper::Initialize(argc, argv,
    vtkProcessModule::PROCESS_BATCH, options);
  //---------------------------------------------------------------------------

  vtkSMSession* session = NULL;
  vtkSMProxy* proxy = NULL;
  if(options->GetUnknownArgument())
    {
    // We have a remote URL to use
    session = vtkSMSessionClient::New();
    session->Initialize();
    vtkSMSessionClient::SafeDownCast(session)->Connect(options->GetUnknownArgument());
    }
  else
    {
    // We are in built-in mode
    session = vtkSMSession::New();
    session->Initialize();
    }

  cout << "Starting..." << endl;

  vtkSMProxyManager* pxm = vtkSMObject::GetProxyManager();

  vtkPVXMLElement* def = pxm->GetProxyDefinitionManager()->
                         GetCollapsedProxyDefinition( "representations",
                                                      "GeometryRepresentation",
                                                      NULL); // GeometryRepresentation Glyph3DRepresentation
  def->PrintXML();

  cout << "Exiting..." << endl;
  session->Delete();

  //---------------------------------------------------------------------------
  vtkInitializationHelper::Finalize();
  options->Delete();
  return return_value;
}