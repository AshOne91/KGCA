
// GameTool2View.cpp: CGameTool2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GameTool2.h"
#endif

#include "GameTool2Doc.h"
#include "GameTool2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameTool2View

IMPLEMENT_DYNCREATE(CGameTool2View, CView)

BEGIN_MESSAGE_MAP(CGameTool2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGameTool2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CGameTool2View 생성/소멸

CGameTool2View::CGameTool2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGameTool2View::~CGameTool2View()
{
}

BOOL CGameTool2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CGameTool2View 그리기

void CGameTool2View::OnDraw(CDC* /*pDC*/)
{
	CGameTool2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CGameTool2View 인쇄


void CGameTool2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGameTool2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGameTool2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGameTool2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CGameTool2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGameTool2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGameTool2View 진단

#ifdef _DEBUG
void CGameTool2View::AssertValid() const
{
	CView::AssertValid();
}

void CGameTool2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameTool2Doc* CGameTool2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameTool2Doc)));
	return (CGameTool2Doc*)m_pDocument;
}
#endif //_DEBUG


// CGameTool2View 메시지 처리기


void CGameTool2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CGameTool2App* pApp = (CGameTool2App*)AfxGetApp();
	pApp->_Sample.ResizeDevice(cx, cy);
}
