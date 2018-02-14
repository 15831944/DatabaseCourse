// ContactManagement.cpp : implementation file
//

#include "stdafx.h"
#include "EmailManagement.h"
#include "ContactManagement.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContactManagement dialog

const CString defaultPath="F:\\���ݿ�γ����\\headPic\\baidu.bmp";
const CString defaultDir="F:\\���ݿ�γ����\\headPic\\";


CContactManagement::CContactManagement(CWnd* pParent /*=NULL*/)
	: CDialog(CContactManagement::IDD, pParent)
{
	//{{AFX_DATA_INIT(CContactManagement)
	m_strCName = _T("");
	m_strCEmail = _T("");
	m_strContactGroup = _T("");
	//}}AFX_DATA_INIT
}


void CContactManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CContactManagement)
	DDX_Control(pDX, IDC_STATIC_HEADPIC, m_headPic);
	DDX_Control(pDX, IDC_COMBO_ALLGROUP, m_cbAllGroup);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_CEMAIL, m_strCEmail);
	DDX_CBString(pDX, IDC_COMBO_ALLGROUP, m_strContactGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CContactManagement, CDialog)
	//{{AFX_MSG_MAP(CContactManagement)
	ON_BN_CLICKED(IDC_STATIC_HEADPIC, OnStaticHeadpic)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContactManagement message handlers

BOOL CContactManagement::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for(int i=0;i<m_strAllGroupArr.GetSize();i++)
	{
		m_cbAllGroup.AddString(m_strAllGroupArr.GetAt(i));
	}
	if(!m_strContactGroup.IsEmpty())
	{
		m_cbAllGroup.SetWindowText(m_strContactGroup);
	}
	else
	{
		m_cbAllGroup.SetCurSel(0);
	}
	if(m_strHeadPath!="")
	{
		MyLoadPic(m_strHeadPath);
	}
	else
	{
		//����Ĭ�ϵ�λͼ
		MyLoadPic(defaultPath);
	}
	if(m_isGroupShow==false)
	{
		GetDlgItem(IDC_COMBO_ALLGROUP)->EnableWindow(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//����λͼ
void CContactManagement::MyLoadPic(CString path)
{
	CRect r; 
	GetDlgItem(IDC_STATIC_HEADPIC)->GetWindowRect(r);
	HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(), 
		path, 
		IMAGE_BITMAP, 
		r.Width()/2, 
		r.Height()/2, 
		LR_LOADFROMFILE);   
	if(hbitmap==NULL)
	{
		MessageBox("�ļ������ڣ�����֮");
	}
	else
	{
		m_headPic.SetBitmap(hbitmap);
	}  
}

//�ϴ�ͼƬ��������¼�
void CContactManagement::OnStaticHeadpic() 
{
	CFileDialog fileDlg(TRUE);
	CString headPath;
	fileDlg.m_ofn.lpstrTitle="�ҵ��ļ��򿪶Ի���";
	fileDlg.m_ofn.lpstrFilter="BitMap Files(*.bmp) \0*.bmp\0 Dib File(*.dib)\0*.dib\0All Files(*.*)\0 *.*\0\0";
	if (IDOK == fileDlg.DoModal())
	{
		headPath = fileDlg.GetFileName();
		CopyFile(headPath,defaultDir+headPath,true);
		m_strHeadPath=defaultDir+headPath;
		MyLoadPic(headPath);
	}
}

void CContactManagement::OnClose() 
{
	//���ǿ�йرնԻ���
	MessageBox("�û�����Email����Ϊ�գ�");
	CDialog::OnClose();
}
