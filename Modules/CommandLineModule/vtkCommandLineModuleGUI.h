/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkGradientAnisotropicDiffusionFilterGUI.h,v $
  Date:      $Date: 2006/03/19 17:12:29 $
  Version:   $Revision: 1.3 $

=========================================================================auto=*/
#ifndef __vtkCommandLineModuleGUI_h
#define __vtkCommandLineModuleGUI_h

#include "vtkSlicerBaseGUIWin32Header.h"
#include "vtkSlicerModuleGUI.h"

#include "vtkMRMLScene.h"
#include "vtkCommandLineModuleLogic.h"

#include "ModuleDescription.h"


class vtkSlicerNodeSelectorWidget;
//BTX
class ModuleWidgetMap;
//ETX

class VTK_COMMANDLINEMODULE_EXPORT vtkCommandLineModuleGUI : public vtkSlicerModuleGUI
{
public:
  static vtkCommandLineModuleGUI *New();
  vtkTypeMacro(vtkCommandLineModuleGUI,vtkSlicerModuleGUI);
  void PrintSelf(ostream& os, vtkIndent indent);

   // Description: Get/Set MRML node
  vtkGetObjectMacro (Logic, vtkCommandLineModuleLogic);
  vtkSetObjectMacro (Logic, vtkCommandLineModuleLogic);
  
  // Description: Get/Set MRML node
  vtkGetObjectMacro (CommandLineModuleNode, vtkMRMLCommandLineModuleNode);
  virtual void SetCommandLineModuleNode(vtkMRMLCommandLineModuleNode*);
  
  // Description: Get the categorization of the module.
  const char *GetCategory() const
    { return this->ModuleDescriptionObject.GetCategory().c_str(); }

  // Description:
  // Get the index of the module.  The index is used for sorting the 
  // modules within a menu. Modules are sorted first by index, then alphabetical
  virtual unsigned short GetIndex() const 
  { return (unsigned short)atol(this->ModuleDescriptionObject.GetIndex().c_str()); }

  // Description:
  // Create widgets
  virtual void BuildGUI ( );

  // Description:
  // Add obsereves to GUI widgets
  virtual void AddGUIObservers ( );
  
  // Description:
  // Remove obsereves to GUI widgets
  virtual void RemoveGUIObservers ( );

  // Description:
  // Remove obsereves to MRML node
  virtual void RemoveMRMLNodeObservers ( );

  // Description:
  // Remove obsereves to Logic
  virtual void RemoveLogicObservers ( );
  
  // Description:
  // Pprocess events generated by Logic
  virtual void ProcessLogicEvents ( vtkObject *caller, unsigned long event,
                                  void *callData ){};

  // Description:
  // Pprocess events generated by GUI widgets
  virtual void ProcessGUIEvents ( vtkObject *caller, unsigned long event,
                                  void *callData );

  // Description:
  // Pprocess events generated by MRML
  virtual void ProcessMRMLEvents ( vtkObject *caller, unsigned long event, 
                                  void *callData);

  // Description:
  // Flags to avoid event loops
  // NOTE: don't use the SetMacro or it call modified itself and generate even more events!
  vtkGetMacro(InMRMLCallbackFlag, int);
  void SetInMRMLCallbackFlag (int flag) {
    this->InMRMLCallbackFlag = flag;
  }
  //
  // Description:
  // Describe behavior at module startup and exit.
  virtual void Enter ( );
  virtual void Exit ( );

  virtual void TearDownGUI ( );
  virtual void CreateModuleEventBindings ( );
  virtual void ReleaseModuleEventBindings ( );
  
  // Description:
  // Get/Set the ModuleDescription object
  const ModuleDescription& GetModuleDescription() const
    { return ModuleDescriptionObject; }
  void SetModuleDescription(const ModuleDescription& description);
//   vtkGetMacro(ModuleDescription, ModuleDescription);
//   vtkSetMacro(ModuleDescription, ModuleDescription);
  

protected:
  // Callback routine that is used for creating a new node.  This
  // method is needed to avoid recursive calls to GUICallback()
  static void NewNodeCallback( vtkObject *__caller,
                              unsigned long eid, void *__clientData, void *callData );    

  vtkCallbackCommand *NewNodeCallbackCommand;

  // Description:
  // Flag to avoid event loops
  int InMRMLCallbackFlag;


private:
  vtkCommandLineModuleGUI();
  virtual ~vtkCommandLineModuleGUI();
  vtkCommandLineModuleGUI(const vtkCommandLineModuleGUI&);
  void operator=(const vtkCommandLineModuleGUI&);

  // Description:
  // Updates GUI widgets based on parameters values in MRML node
  void UpdateGUI();

  // Description:
  // Updates parameters values in MRML node based on GUI widgets 
  void UpdateMRML();
  
  ModuleDescription ModuleDescriptionObject;  

  ModuleWidgetMap *InternalWidgetMap;

  vtkCommandLineModuleLogic *Logic;
  vtkMRMLCommandLineModuleNode* CommandLineModuleNode;

  bool CreatingNewNode;
  bool InUpdateMRML;
  bool InUpdateGUI;

};

#endif

