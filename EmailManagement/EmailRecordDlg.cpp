// EmailRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EmailManagement.h"
#include "EmailRecordDlg.h"

#include "EmailManagementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmailRecordDlg dialog

const CString constFujianName="���������������ļ�ȫ��";
const CString constFujianDesc="�����븽�����������";

const CString dir="F:\\���ݿ�γ����\\image\\";

CEmailRecordDlg::CEmailRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmailRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmailRecordDlg)
	m_strContact = _T("");
	m_strEtype = _T("");
	m_sendDate = COleDateTime::GetCurrentTime();
	m_strEmailInfo = _T("");
	m_isFujian = FALSE;
	m_strFileName = constFujianName;
	m_strFujianDesc = constFujianDesc;
	m_isRead = FALSE;
	m_strGroup = _T("");
	m_isQunfa = FALSE;
	m_strReceiverSeq = _T("");
	m_isDraft = FALSE;
	//}}AFX_DATA_INIT

	flag=false;
}


void CEmailRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmailRecordDlg)
	DDX_Control(pDX, IDC_FUJIAN_PIC, m_Picture);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_cbGroup);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbEtype);
	DDX_Control(pDX, IDC_COMBO_CONTACT, m_cbContact);
	DDX_CBString(pDX, IDC_COMBO_CONTACT, m_strContact);
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_strEtype);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER, m_sendDate);
	DDX_Text(pDX, IDC_EDIT_EINFO, m_strEmailInfo);
	DDX_Check(pDX, IDC_CHECK_FUJIAN, m_isFujian);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_FILE_DESC, m_strFujianDesc);
	DDX_Check(pDX, IDC_CHECK_ISREAD, m_isRead);
	DDX_CBString(pDX, IDC_COMBO_GROUP, m_strGroup);
	DDX_Check(pDX, IDC_CHECK_ISQUNFA, m_isQunfa);
	DDX_Text(pDX, IDC_EDIT_RECIEVER_SEQ, m_strReceiverSeq);
	DDX_Check(pDX, IDC_CHECK_DRAFT, m_isDraft);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmailRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CEmailRecordDlg)
	ON_BN_CLICKED(IDC_CHECK_FUJIAN, OnCheckFujian)
	ON_EN_SETFOCUS(IDC_EDIT_FILE_NAME, OnSetfocusEditFileName)
	ON_EN_SETFOCUS(IDC_EDIT_FILE_DESC, OnSetfocusEditFileDesc)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTACT, OnSelchangeComboContact)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	ON_EN_KILLFOCUS(IDC_EDIT_FILE_NAME, OnKillfocusEditFileName)
	ON_BN_CLICKED(IDC_BTN_UPLOAD, OnBtnUpload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmailRecordDlg message handlers

void CEmailRecordDlg::OnOK() 
{
	if(!UpdateData())
	{
		return ;
	}
	//�ʼ����Ͳ���Ϊ��
	if(m_strEtype.IsEmpty())
	{
		AfxMessageBox("�ʼ�����Ϊ�գ���ѡ���ʼ�����");
		return;
	}
	//�ռ����������ܹ�Ϊ��
	if(m_strContact.IsEmpty())
	{
		AfxMessageBox("�ռ�������Ϊ�գ�������ѡ���ռ�������");
		return;
	}
	//����������Ϊ��
	if(m_strFileName.IsEmpty())
	{
		AfxMessageBox("������Ϊ�գ�������ѡ���ռ�������");
		return;
	}
	UpdateData(TRUE);
	if(this->m_isRead==TRUE)
	{
		CString sql;
		sql.Format("update email_record_tab set ISREAD=%d where RECORD_ID=%d",1,this->m_nRecordID);
		TRACE(sql);
		((CEmailManagementDlg*)GetParent())->GetDB()->ExecuteSQL(sql);
	}

	CDialog::OnOK();
}

BOOL CEmailRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//����ϵ���б���������ϵ����������
	for(int i=0;i<m_strContactArray.GetSize();i++)
	{
		m_cbContact.AddString(m_strContactArray.GetAt(i));
	}
	//����ǲ鿴��¼�����б����ı�ֵΪҪ�鿴���ռ��˵�����
	if(!m_strContact.IsEmpty())
	{
		m_cbContact.SetWindowText(m_strContact);
	}
	else
	{
		m_cbContact.SetCurSel(0);//����Ƿ��ͣ����б����ı�ֵĬ��Ϊ�б������ϵ���б��еĵ�һ��
	}
	
	//���ʼ������б��ؼ������������Ϣ
	for(i=0;i<m_strTypeArray.GetSize();i++)
	{
		m_cbEtype.AddString(m_strTypeArray.GetAt(i));
	}
	//����ǲ鿴�ʼ�������Ϣ��¼�����б���ֵΪҪ�鿴���ʼ�����
	if(!m_strEtype.IsEmpty())
	{
		m_cbEtype.SetWindowText(m_strEtype);
	}
	else
	{
		//����Ƿ����ʼ������б����ı�ֵĬ��Ϊ�б�����ʼ��б������еĵ�һ��
		m_cbEtype.SetCurSel(0);
	}

	//��ʼ�������Ͽ�
	for(i=0;i<m_strGroupArr.GetSize();i++)
	{
		m_cbGroup.AddString(m_strGroupArr.GetAt(i));
	}
	if(!m_strGroup.IsEmpty())
	{
		m_cbGroup.SetWindowText(m_strGroup);
	}
	else
	{
		m_cbGroup.SetCurSel(0);
	}

	//��ʼʱ�������ļ����༭����ʾ
	GetDlgItem(IDC_EDIT_FILE_NAME)->ShowWindow(false);
	GetDlgItem(IDC_EDIT_FILE_DESC)->ShowWindow(false);
	GetDlgItem(IDC_BTN_UPLOAD)->ShowWindow(false);
	
	//��ʼʱ���Ѷ���ǲ���ʾ
	GetDlgItem(IDC_CHECK_ISREAD)->ShowWindow(false);
	//��ʼʱ�������ʼ�Ⱥ��
	GetDlgItem(IDC_EDIT_RECIEVER_SEQ)->ShowWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmailRecordDlg::OnCheckFujian() 
{
	if(flag==false)
	{
		GetDlgItem(IDC_EDIT_FILE_NAME)->ShowWindow(true);
		GetDlgItem(IDC_EDIT_FILE_DESC)->ShowWindow(true);
		GetDlgItem(IDC_BTN_UPLOAD)->ShowWindow(true);
		flag=true;
	}
	else
	{
		GetDlgItem(IDC_EDIT_FILE_NAME)->ShowWindow(false);
		GetDlgItem(IDC_EDIT_FILE_DESC)->ShowWindow(false);
		GetDlgItem(IDC_BTN_UPLOAD)->ShowWindow(false);
		flag=false;
	}
}

void CEmailRecordDlg::OnSetfocusEditFileName() 
{
	UpdateData(true);
	if(m_strFileName==constFujianName)
	{
		m_strFileName="";
		UpdateData(false);
	}
}

void CEmailRecordDlg::OnSetfocusEditFileDesc() 
{
	UpdateData(true);
	if(m_strFujianDesc==constFujianDesc)
	{
		m_strFujianDesc="";
		UpdateData(false);
	}
}

void CEmailRecordDlg::GetRecordID(int RecordID)
{
	this->m_nRecordID=RecordID;
}

void CEmailRecordDlg::OnSelchangeComboContact() 
{
	TRY
	{
		UpdateData(true);
		int nIndex=m_cbContact.GetCurSel();
		m_strContact=m_strContactArray.GetAt(nIndex);
		m_strGroup="";
		
		if(m_isQunfa==TRUE)
		{
			m_strReceiverSeq+=m_strContact;
			m_strReceiverSeq+=";";
			GetDlgItem(IDC_EDIT_RECIEVER_SEQ)->ShowWindow(true);
			GetDlgItem(IDC_EDIT_RECIEVER_SEQ)->EnableWindow(false);
			m_strReceiverArr.Add(m_strContact);
		}


		CRecordset rs;
		rs.m_pDatabase=((CEmailManagementDlg*)GetParent())->GetDB();		
		
		CString sql;
		sql.Format("select * from contact_info_tab,contact_group\
					where\
					contact_info_tab.group_id=contact_group.group_id\
					and contact_info_tab.contact_name='%s'",m_strContact);
		
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			m_strGroup="";
			rs.GetFieldValue(7,m_strGroup);
			rs.MoveNext();
		}
		rs.Close();

		UpdateData(FALSE);
	}
	CATCH(CDBException,ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException,pEx)
	{
		pEx->ReportError();
		AfxMessageBox("memory exception");
	}
	AND_CATCH(CException,e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
	END_CATCH
}

//����������ѡ������ʱ��Ӱ����ϵ��
void CEmailRecordDlg::OnSelchangeComboGroup() 
{
	TRY
	{
		UpdateData(true);
		int nIndex=m_cbGroup.GetCurSel();
		m_strGroup=m_strGroupArr.GetAt(nIndex);
		int num=m_cbContact.GetCount();
		for(int i=num-1;i>=0;i--)
		{
			m_cbContact.DeleteString(i);
		}
		m_strContact="";

		CRecordset rs;
		rs.m_pDatabase=((CEmailManagementDlg*)GetParent())->GetDB();		
		
		CString sql;
		sql.Format("select * from contact_info_tab,contact_group\
					where\
					contact_info_tab.group_id=contact_group.group_id\
					and contact_group.group_name='%s'",m_strGroup);
		
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			m_strContact="";
			rs.GetFieldValue(1,m_strContact);
			m_cbContact.AddString(m_strContact);
			rs.MoveNext();
		}
		rs.Close();

		UpdateData(FALSE);
	}
	CATCH(CDBException,ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CMemoryException,pEx)
	{
		pEx->ReportError();
		AfxMessageBox("memory exception");
	}
	AND_CATCH(CException,e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
	END_CATCH
	
}

//�������λͼ�Ļ�������ʾԤ��
void CEmailRecordDlg::LoadPic()
{
	CString fujianName=m_strFileName;
    CString nameTear;
	nameTear=GetSuffix(fujianName);
	if(nameTear=="png" || nameTear=="jpg" ||nameTear=="bmp" || nameTear=="jpeg")
	{
		CRect r; 
		GetDlgItem(IDC_FUJIAN_PIC)->GetWindowRect(r);
		HBITMAP hbitmap=(HBITMAP)LoadImage(AfxGetInstanceHandle(), 
           dir+fujianName, 
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
			m_Picture.SetBitmap(hbitmap);
		   MessageBox("�ļ�λ�ã�"+dir+fujianName);
		}  
	}
	else
	{
		MessageBox("�ļ�λ�ã�"+dir+fujianName+"�����ļ������ṩԤ��");
	}
}

void CEmailRecordDlg::OnKillfocusEditFileName() 
{
	UpdateData(true);
	LoadPic();
	UpdateData(false);
}

//����ļ�����չ��
CString CEmailRecordDlg::GetSuffix(CString strFileName)
{
	return strFileName.Right(strFileName.GetLength()-strFileName.ReverseFind('.')-1);
}


void CEmailRecordDlg::OnBtnUpload() 
{
	CFileDialog fileDlg(TRUE);
	CString fujianPath;
	fileDlg.m_ofn.lpstrTitle="�ҵ��ļ��򿪶Ի���";
	if (IDOK == fileDlg.DoModal())
	{
		UpdateData(true);
		fujianPath = fileDlg.GetFileName();
		CopyFile(fujianPath,dir+fujianPath,true);
		m_strFileName=fujianPath;
		LoadPic();
		UpdateData(false);
	}
}


