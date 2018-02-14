// EmailDraftDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EmailManagement.h"
#include "EmailDraftDlg.h"

#include "EmailManagementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmailDraftDlg dialog


CEmailDraftDlg::CEmailDraftDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmailDraftDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmailDraftDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEmailDraftDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmailDraftDlg)
	DDX_Control(pDX, IDC_LIST_DRAFT, m_listDraft);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmailDraftDlg, CDialog)
	//{{AFX_MSG_MAP(CEmailDraftDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmailDraftDlg message handlers

BOOL CEmailDraftDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitListControl();
	InitListData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmailDraftDlg::InitListControl()
{
		//�����б�ؼ�����չ���
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_listDraft.SetExtendedStyle(dwExStyle);
	
	//��ʼ���ʼ���¼�б�ؼ�
	m_listDraft.InsertColumn(0,"��¼ ID",LVCFMT_CENTER,60);
	m_listDraft.InsertColumn(1,"����",LVCFMT_CENTER,60);
	m_listDraft.InsertColumn(2,"�ʼ���������",LVCFMT_CENTER,140);
	m_listDraft.InsertColumn(3,"��Ӹ���",LVCFMT_CENTER,60);
	m_listDraft.InsertColumn(4,"�ʼ�����",LVCFMT_CENTER,60);
	m_listDraft.InsertColumn(5,"�ʼ�����",LVCFMT_CENTER,200);
	m_listDraft.InsertColumn(6,"������",LVCFMT_CENTER,140);
}

void CEmailDraftDlg::InitListData()
{
	InitDraftListControl();
}

//��ʼ���ݸ����б�ؼ�
void CEmailDraftDlg::InitDraftListControl()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=((CEmailManagementDlg*)GetParent())->GetDB();
		CString sql;
		
		//��ʼ������վ�б�ؼ�
		sql.Format("select * from Email_record_tab where IS_DRAFT=1 and RECORD_ID in(select RECORD_ID \
			from user_own where USER_ID=%d)",((CEmailManagementDlg*)GetParent())->GetCurUserID());
		rs.Open(CRecordset::dynaset,sql);

		int recordID,contactID,isFujian,typeID,fujianID;
		CString email,sendDate,emailTxt,strName,strType,fujianName;
		
		while(!rs.IsEOF())
		{
			recordID=-1;contactID=-1;isFujian=-1;typeID=-1;fujianID=-1;
			email="";	sendDate="";	emailTxt="";	strName="";		strType="";	fujianName="";
			
			CDBVariant var;
			//��ȡ�ʼ�ID�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				recordID=var.m_iVal;
			var.Clear();
			//��ȡ�ռ���ID�ֶ�ֵ
			rs.GetFieldValue(1,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				contactID=var.m_iVal;
			var.Clear();
			//��ȡ�ʼ����������ֶ�ֵ
			rs.GetFieldValue(2,sendDate);
			//��ȡ�Ƿ���Ӹ����ֶ�ֵ
			rs.GetFieldValue(3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				isFujian=var.m_iVal;
			var.Clear();
			//��ȡ�ʼ�����ID�ֶ�ֵ
			rs.GetFieldValue(4,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				typeID=var.m_iVal;
			var.Clear();
			//��ȡ�ʼ���Ϣ�����ֶ�ֵ
			rs.GetFieldValue(5,emailTxt);
			//��ȡ����ID�ֶ�ֵ
			rs.GetFieldValue(6,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				fujianID=var.m_iVal;
			var.Clear();
			
			CRecordset rs2(((CEmailManagementDlg*)GetParent())->GetDB());
			//ͨ����ϵ��ID�����ϵ������
			CString temp;
			temp.Format("select contact_name from contact_info_tab where ""contact_id=%d",contactID);
			rs2.Open(CRecordset::dynaset,temp);
			if(!rs2.IsEOF())
			{
				rs2.GetFieldValue((short)0,strName);
			}
			rs2.Close();
			
			//ͨ���ʼ�����ID��ȡ�ʼ���������
			temp.Format("select type_name from email_type_tab where ""type_id=%d",typeID);
			rs2.Open(CRecordset::dynaset,temp);
			if(!rs2.IsEOF())
			{
				rs2.GetFieldValue((short)0,strType);
			}
			rs2.Close();
			
			//ͨ������ID��ø��������Ƶ�����
			temp.Format("select fname from email_fujian where fid=%d",fujianID);
			rs2.Open(CRecordset::dynaset,temp);
			if(!rs2.IsEOF())
			{
				rs2.GetFieldValue((short)0,fujianName);
			}
			rs2.Close();
			
			//���ʼ��б�ؼ��м���һ���µļ�¼��Ϣ
			ReadDraftInfo(recordID,strName,sendDate,isFujian,strType,emailTxt,fujianName);
			rs.MoveNext();
		}
		rs.Close();
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

void CEmailDraftDlg::ReadDraftInfo(int recordID, \
	CString strName, CString sendDate, int isFujian, CString strType, CString emailTxt, CString fujianName)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listDraft.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",recordID);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_listDraft.InsertItem(&lvItem);
	m_listDraft.SetItemText(nIndex,1,strName);
	m_listDraft.SetItemText(nIndex,2,sendDate);
	m_listDraft.SetItemText(nIndex,3,isFujian==0?"��":"��");
	m_listDraft.SetItemText(nIndex,4,strType);
	m_listDraft.SetItemText(nIndex,5,emailTxt);
	m_listDraft.SetItemText(nIndex,6,fujianName);
}
