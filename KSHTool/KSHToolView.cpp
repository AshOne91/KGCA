
// KSHToolView.cpp: CKSHToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "KSHTool.h"
#endif

#include "KSHToolDoc.h"
#include "KSHToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKSHToolView

IMPLEMENT_DYNCREATE(CKSHToolView, CView)

BEGIN_MESSAGE_MAP(CKSHToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKSHToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CKSHToolView 생성/소멸

CKSHToolView::CKSHToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CKSHToolView::~CKSHToolView()
{
}

BOOL CKSHToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CKSHToolView 그리기

void CKSHToolView::OnDraw(CDC* /*pDC*/)
{
	CKSHToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CKSHToolView 인쇄


void CKSHToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKSHToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CKSHToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CKSHToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CKSHToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKSHToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKSHToolView 진단

#ifdef _DEBUG
void CKSHToolView::AssertValid() const
{
	CView::AssertValid();
}

void CKSHToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKSHToolDoc* CKSHToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKSHToolDoc)));
	return (CKSHToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CKSHToolView 메시지 처리기


void CKSHToolView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CKSHToolApp* pApp = (CKSHToolApp*)AfxGetApp();
	pApp->_Sample.ResizeDevice(cx, cy);
}
