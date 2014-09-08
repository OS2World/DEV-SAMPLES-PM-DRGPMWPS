
/*
 * This file was generated by the SOM Compiler.
 * FileName: drgagent.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

#pragma info( none )
#define DrgAgent_Class_Source
#include "DrgAgent.ih"
#pragma info( restore )

#include "common.h"

int  _CRT_init( void );
void _CRT_term( void );

HMODULE hmodUs = 0;

ULONG APIENTRY _DLL_InitTerm( ULONG ulHMod, ULONG fl )
{
    if( fl )                        // Termination time if non-zero
    {
        _CRT_term();
    }
    else
    {
        if( _CRT_init() == -1 )     // -1 means not successful
            return 0;               // 0 means initialization failed

        hmodUs = ulHMod;            // The whole purpose for this init routine
    }

    return 1;                       // non-zero indicates init successful
}

SOM_Scope MRESULT   SOMLINK Agent_wpDraggedOverObject(DrgAgent *somSelf,
		WPObject *DraggedOverObject)
{
    DrgAgentData *somThis = DrgAgentGetData(somSelf);
    DrgAgentMethodDebug("DrgAgent","Agent_wpDraggedOverObject");

    // Allow all drops.

    parent_wpDraggedOverObject( somSelf, DraggedOverObject );

    return MRFROM2SHORT( DOR_DROP, DO_COPY );
}


SOM_Scope BOOL   SOMLINK Agent_wpDroppedOnObject(DrgAgent *somSelf,
		WPObject *DroppedOnObject)
{
    DrgAgentData *somThis = DrgAgentGetData(somSelf);
    DrgAgentMethodDebug("DrgAgent","Agent_wpDroppedOnObject");

    // Tell the object window that we were dropped on.

    parent_wpDroppedOnObject( somSelf, DroppedOnObject );

    return (BOOL) WinSendMsg( _hwndComm, UM_DROP, MPFROMP( DroppedOnObject ),
                              NULL );
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
SOM_Scope ULONG   SOMLINK AgentCls_wpclsQueryIconData(M_DrgAgent *somSelf,
		PICONINFO pIconInfo)
{
    /* M_DrgAgentData *somThis = M_DrgAgentGetData(somSelf); */
    M_DrgAgentMethodDebug("M_DrgAgent","AgentCls_wpclsQueryIconData");

    SOM_TraceLevel = 2;

    if( pIconInfo )
    {
        pIconInfo->hmod    = hmodUs;
        pIconInfo->resid   = IID_DEFICON;
        pIconInfo->fFormat = ICON_RESOURCE;
    }

    return sizeof( *pIconInfo );
}

SOM_Scope ULONG   SOMLINK AgentCls_wpclsQueryStyle(M_DrgAgent *somSelf)
{
    /* M_DrgAgentData *somThis = M_DrgAgentGetData(somSelf); */
    M_DrgAgentMethodDebug("M_DrgAgent","AgentCls_wpclsQueryStyle");

    return (parent_wpclsQueryStyle(somSelf) |
        CLSSTYLE_NEVERTEMPLATE | CLSSTYLE_NEVERPRINT);
}

SOM_Scope PSZ   SOMLINK AgentCls_wpclsQueryTitle(M_DrgAgent *somSelf)
{
    /* M_DrgAgentData *somThis = M_DrgAgentGetData(somSelf); */
    M_DrgAgentMethodDebug("M_DrgAgent","AgentCls_wpclsQueryTitle");

    return CLASS_TITLE;
}

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta
SOM_Scope void   SOMLINK AgentCls_wpclsInitData(M_DrgAgent *somSelf)
{
    /* M_DrgAgentData *somThis = M_DrgAgentGetData(somSelf); */
    M_DrgAgentMethodDebug("M_DrgAgent","AgentCls_wpclsInitData");

    // Create the object window used to communicate with the PM window

    CommwinCreate( somSelf );

    parent_wpclsInitData(somSelf);
}

SOM_Scope void   SOMLINK AgentCls_wpclsUnInitData(M_DrgAgent *somSelf)
{
    /* M_DrgAgentData *somThis = M_DrgAgentGetData(somSelf); */
    M_DrgAgentMethodDebug("M_DrgAgent","AgentCls_wpclsUnInitData");

    // Destroy the object window

    CommwinDestroy();

    // Let the window be destroyed before the parent calls DosFreeModule on us

    DosSleep( 2500 );

    parent_wpclsUnInitData(somSelf);
}
