// EmailManagementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EmailManagement.h"
#include "EmailManagementDlg.h"

#include "ContactManagement.h"
#include "EmailTypeDlg.h"
#include "EmailRecordDlg.h"
#include "TimeQueryDlg.h"
#include "EmailContactGroupDlg.h"
#include "DBConnDlg.h"
#include "UserLogon.h"
#include "UserRegistDlg.h"
#include "AllUsersDlg.h"
#include "BlurFindDlg.h"
#include "Base64Date6.h"
#include "EmailDraftDlg.h"
#include "MyEmailSendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
const CString dir="F:\\���ݿ�γ����\\image\\";

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmailManagementDlg dialog

CEmailManagementDlg::CEmailManagementDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEmailManagementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmailManagementDlg)
	m_strUserTishi = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_EMAIL);
	
	m_strDBSource="ORCLClient";
	m_strUserName="scott";
	m_strPassword="955219Sh";
}

void CEmailManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmailManagementDlg)
	DDX_Control(pDX, IDC_LIST_BLACK, m_listBlack);
	DDX_Control(pDX, IDC_LIST_RECYCLE_BIN, m_listRecycleBin);
	DDX_Control(pDX, IDC_LIST_FUJIAN, m_listFujian);
	DDX_Control(pDX, IDC_LIST_GROUP, m_listGroup);
	DDX_Control(pDX, IDC_LIST_RECORD, m_listRecord);
	DDX_Control(pDX, IDC_LIST_ETYPE, m_listType);
	DDX_Control(pDX, IDC_LIST_CONTACT, m_listContact);
	DDX_Text(pDX, IDC_STATIC_TISHI, m_strUserTishi);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmailManagementDlg, CDialog)
//{{AFX_MSG_MAP(CEmailManagementDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTN_ADDCON, OnBtnAddcon)
ON_BN_CLICKED(IDC_BTN_DELCON, OnBtnDelcon)
ON_BN_CLICKED(IDC_BTN_MODCON, OnBtnModcon)
ON_BN_CLICKED(IDC_BTN_ADDTYPE, OnBtnAddtype)
ON_BN_CLICKED(IDC_BTN_DELTYPE, OnBtnDeltype)
ON_BN_CLICKED(IDC_BTN_MODTYPE, OnBtnModtype)
ON_BN_CLICKED(IDC_BTN_SENDRED, OnBtnSendred)
ON_BN_CLICKED(IDC_BTN_QUERYRED, OnBtnQueryred)
ON_BN_CLICKED(IDC_BTNDELRED, OnBtndelred)
ON_BN_CLICKED(IDC_BUTTON_TIMEQUERY, OnButtonTimequery)
ON_BN_CLICKED(IDC_BTN_GROUP_ADD, OnBtnGroupAdd)
ON_BN_CLICKED(IDC_BTN_GROUP_QUERY, OnBtnGroupQuery)
ON_BN_CLICKED(IDC_BTN_GROUP_DEL, OnBtnGroupDel)
ON_BN_CLICKED(IDC_BTN_READED, OnBtnReaded)
ON_BN_CLICKED(IDC_BTN_NOTREAD, OnBtnNotread)
ON_BN_CLICKED(IDC_BTN_MOVETO_BIN, OnBtnMovetoBin)
ON_BN_CLICKED(IDC_BTN_RESTORE, OnBtnRestore)
ON_BN_CLICKED(IDC_BTN_MOVETO_BLACK_LIST, OnBtnMovetoBlackList)
ON_BN_CLICKED(IDC_BTN_RETURNTO_CONTACT, OnBtnReturntoContact)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_CONTACT, OnColumnclickListContact)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_ETYPE, OnColumnclickListEtype)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_RECORD, OnColumnclickListRecord)
ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_RECYCLE_BIN, OnColumnclickListRecycleBin)
ON_COMMAND(IDM_DB, OnDb)
ON_WM_DESTROY()
ON_COMMAND(IDM_CHANGE_MY_SKIN, OnChangeMySkin)
ON_COMMAND(IDM_REMOVE_SKIN, OnRemoveSkin)
ON_COMMAND(IDM_LOG_ON, OnLogOn)
ON_COMMAND(IDM_USER_REGIST, OnUserRegist)
ON_COMMAND(IDM_ALL_USERS, OnAllUsers)
ON_NOTIFY(NM_CLICK, IDC_LIST_FUJIAN, OnClickListFujian)
ON_BN_CLICKED(IDC_BTN_RECEIVE_BIN, OnBtnReceiveBin)
ON_BN_CLICKED(IDC_BTN_SEND_BIN, OnBtnSendBin)
ON_BN_CLICKED(IDC_BTN_BLUR_FIND, OnBtnBlurFind)
ON_COMMAND(IDM_NET_SEND_MAIL, OnNetSendMail)
	ON_BN_CLICKED(IDC_BTN_DRAFT, OnBtnDraft)
	ON_COMMAND(IDM_USER_CANCELLATION, OnUserCancellation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmailManagementDlg message handlers

BOOL CEmailManagementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitListControl();
	//���ӵ����ݿ�
	ConnDB();
	
	CMenu *menu = new CMenu;
	menu ->LoadMenu(MAKEINTRESOURCE(IDR_MENU_YOUJIAN)); //IDR_MENU �˵�ID
	this ->SetMenu(menu);
	
	//��ʾ��ǰ�û����ȼ�
	UpdateData(true);
	CString tmepUser;
	if(""==m_strCurUser)
	{
		tmepUser="���ܵĹ���Ա";
		m_strUserTishi="��ǰ�û���"+tmepUser+" ";
		m_strUserTishi=m_strUserTishi+"�û��ȼ���"+"super vip";
	}
	UpdateData(false);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEmailManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEmailManagementDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEmailManagementDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//���ӵ����ݿ�
void CEmailManagementDlg::ConnDB()
{
	if(m_db.IsOpen())
	{
		AfxMessageBox("���ݿ��Ѿ�����");
		return;
	}
	if(m_strDBSource.IsEmpty()||m_strUserName.IsEmpty()||m_strPassword.IsEmpty())
	{
		AfxMessageBox("���ݿ����ò������ܹ�Ϊ��");
		return;
	}
	CString strConnect;
	strConnect.Format("DSN=%s;UID=%s;PWD=%s;QTO=F",m_strDBSource,m_strUserName,m_strPassword);
    TRY
	{
		m_db.OpenEx(strConnect,CDatabase::noOdbcDialog);
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
		InitListData();
}

//�����ϵ��ID�����ֵ
int CEmailManagementDlg::GetNewContactID()
{
	TRY
	{
		CRecordset rs(&m_db);
		rs.Open(CRecordset::dynaset,"select max(contact_id) from contact_info_tab");
		
		//��������Ӽ�¼����ϵ�˵�IDֵ
		int newContactID=1;
		//������ݿ������м�¼�ˣ����µ���ϵ��ID=��ϵ�˵�ID���ֵ��1
		if(!rs.IsEOF())
		{
			CDBVariant var;
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				newContactID=var.m_iVal+1;
			}
		}
		rs.Close();
		return newContactID;
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
		return -1;
}

//ִ��sql���
void CEmailManagementDlg::MyExecuteSQL(CString sql)
{
	TRY
	{
		TRACE(sql);
		m_db.ExecuteSQL(sql);
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

//������ϵ�˵���Ϣ
void CEmailManagementDlg::OnBtnAddcon() 
{
	//����һ����ϵ�˶Ի���ʵ��
	CContactManagement dlg;
	
	//������û���û����ϵ�˷���
	if(m_listGroup.GetItemCount()==0)
	{
		dlg.m_isGroupShow=false;
	}
	
	CString sql;
	CString tempGroupName;
	
	//Ϊ���������ֵ
	CRecordset rs2;
	rs2.m_pDatabase=&m_db;
	if(m_strCurUser=="")
	{
		sql.Format("select * from contact_group");
	}
	else
	{
		sql.Format("select * from contact_group where group_id in(select group_id from user_own where user_id=%d)",GetCurUserID());
	}
	rs2.Open(CRecordset::dynaset,sql);
	while(!rs2.IsEOF())
	{
		rs2.GetFieldValue(1,tempGroupName);
		dlg.m_strAllGroupArr.Add(tempGroupName);
		rs2.MoveNext();
	}
	rs2.Close();
	
	if(dlg.DoModal()==IDOK)
	{
		//�ӶԻ����л�ȡ������Email����
		CString strName=dlg.m_strCName;
		CString strEmail=dlg.m_strCEmail;
		CString strPath=dlg.m_strHeadPath;
		
		//�Ƿ������Ԥ����
		if(""==strName || ""==strEmail)
		{
			MessageBox("�û������ʼ���ַ����Ϊ�գ�");
			return;
		}
		
		TRY
		{
			//�򿪼�¼��
			int tempGroupID=0;
			CRecordset rs(&m_db);
			rs.Open(CRecordset::dynaset,"select max(contact_id) from contact_info_tab");
			
			//��������Ӽ�¼����ϵ�˵�IDֵ
			int newContactID=1;
			//������ݿ������м�¼�ˣ����µ���ϵ��ID=��ϵ�˵�ID���ֵ��1
			if(!rs.IsEOF())
			{
				CDBVariant var;
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					newContactID=var.m_iVal+1;
				}
			}
			rs.Close();
			
            if(dlg.m_strContactGroup!="")
			{
				//���Ҫ��ӵ������ϵ�˵�id
				sql.Format("select * from contact_group where GROUP_NAME='%s'",dlg.m_strContactGroup);
				rs.Open(CRecordset::dynaset,sql);
				while(!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var,SQL_C_SLONG);
					if(var.m_dwType!=DBVT_NULL)
					{
						tempGroupID=var.m_iVal;
					}
					rs.MoveNext();
				}
				rs.Close();

				if(0==tempGroupID)
				{
					MessageBox("��ϵ�˵ķ��鲢�����ڣ��������֮");
					return;
				}
			}

			//������������ϵ�˼�¼���ַ���
			CString sql;
			sql.Format("insert into contact_info_tab(contact_id,""contact_name,e_mail,GROUP_ID,IS_BLACK,HEAD_PIC_PATH) \
				values(""%d,'%s','%s','%d',%d,'%s')",newContactID,strName,strEmail,tempGroupID,0,strPath);
			TRACE(sql);
			//�µ���ϵ�˼�¼���뵽���ݿ���
			m_db.ExecuteSQL(sql);
			if(m_strCurUser!="")
			{
			sql.Format("insert into user_own(USER_ID,CONTACT_ID,RECORD_ID,GROUP_ID,FUJIAN_ID) \
				values(%d,%d,%d,%d,%d)",GetCurUserID(),newContactID,0,tempGroupID,0,0);
			TRACE(sql);
			//�µ���ϵ�˼�¼���뵽���ݿ���
			m_db.ExecuteSQL(sql);
			}
			//���µ���ϵ�˼�¼����Ϣ��ʾ���б�ؼ���
			ReadcontactInfo(newContactID,strName,strEmail,dlg.m_strContactGroup);
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}
	else
	{
		return;
	}
}

//���������Ϣ
void CEmailManagementDlg::OnBtnGroupAdd() 
{
	//����һ����ϵ�˶Ի���ʵ��
	CEmailContactGroupDlg dlg;
	dlg.m_AddOrLook=ADD;
	if(dlg.DoModal()==IDOK)
	{
		//�ӶԻ����л�ȡ������Email����
		CString strName=dlg.m_strGroupName;
		CString strDesc=dlg.m_strGroupDesc;

		if(""==strName || ""==strDesc)
		{
			MessageBox("�������鱸ע����Ϊ��");
			return;
		}

		TRY
		{
			//�򿪼�¼��
			CRecordset rs(&m_db);
			rs.Open(CRecordset::dynaset,"select max(group_id) from contact_group");
			//��������Ӽ�¼����ϵ�˵�IDֵ
			int newGroupID=1;
			//������ݿ������м�¼�ˣ����µ���ϵ��ID=��ϵ�˵�ID���ֵ��1
			if(!rs.IsEOF())
			{
				CDBVariant var;
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					newGroupID=var.m_iVal+1;
				}
			}
			//������������ϵ�˼�¼���ַ���
			CString sql;
			sql.Format("insert into contact_group(group_id,""group_name,group_desc)""values(""%d,'%s','%s')",newGroupID,strName,strDesc);
			TRACE(sql);
			//�µ���ϵ�˼�¼���뵽���ݿ���
			m_db.ExecuteSQL(sql);
			if(m_strCurUser!="")
			{
				sql.Format("insert into user_own(USER_ID,CONTACT_ID,RECORD_ID,GROUP_ID) values(%d,0,0,%d)",GetCurUserID(),newGroupID);
				TRACE(sql);
				m_db.ExecuteSQL(sql);
			}
			//���µ���ϵ�˼�¼����Ϣ��ʾ���б�ؼ���
			ReadContactGroupInfo(newGroupID,strName,strDesc);
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}
}


//ɾ����ϵ�˵���Ϣ
void CEmailManagementDlg::OnBtnDelcon() 
{
	if(IDOK==MessageBox("��ȷ��Ҫɾ�������ϵ���𣿣������ڴ���ϵ�˵ļ�¼Ҳ��ɾ����","����",MB_OKCANCEL))
	{
		//��ȡҪɾ������ϵ�˵ļ�¼���ڵ���
		int cItem=m_listContact.GetNextItem(-1,LVNI_SELECTED);
		if(cItem==-1)
		{
			AfxMessageBox("û��ѡ��Ҫɾ������ϵ�ˣ�");
			return;
		}
		//���Ҫɾ������ϵ�˵�id
		int id=atoi(m_listContact.GetItemText(cItem,0));
		TRY
		{
			CString sql;
			//��ѯ��������¼��

			//�����ݿ���ɾ����¼
			sql.Format("delete contact_info_tab where contact_id=%d",id);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
             
			//ɾ���û�����ؼ�¼
			sql.Format("delete user_own where contact_id=%d and user_id=%d",id,GetCurUserID());
			TRACE(sql);
			m_db.ExecuteSQL(sql);
			
			//���б�ؼ���ɾ���ü�¼
			m_listContact.DeleteItem(cItem);
			GetCurUserIdInfo();
			CurUserChangeInit();
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}
	else
	{
		MessageBox("��ϵ�˲�δɾ����");
	}
}

//�޸���ϵ�˵���Ϣ
void CEmailManagementDlg::OnBtnModcon() 
{
	//ѡ��Ҫ�޸ĵļ�¼��
	int cItem=m_listContact.GetNextItem(-1,LVNI_SELECTED);
	if(cItem==-1)
	{
		AfxMessageBox("û��ѡ��Ҫ�޸ĵ���ϵ�ˣ�");
		return;
	}
	//��õ�cItem���е���Ϣ
	int id=atoi(m_listContact.GetItemText(cItem,0));
	CString name=m_listContact.GetItemText(cItem,1);
	CString strEmail=m_listContact.GetItemText(cItem,2);
	//������ϵ�˶Ի���ʵ��
	CContactManagement dlg;
	dlg.m_strCName=name;
	dlg.m_strCEmail=strEmail;
	
	TRY
	{
		CString sql;
		CString path;
		
		CRecordset rs(&m_db);
		sql.Format("select * from contact_info_tab where CONTACT_ID=%d",id);
		rs.Open(CRecordset::dynaset,sql);
		if(!rs.IsEOF())
		{
			rs.GetFieldValue(5,dlg.m_strHeadPath);
		}
	}
	CATCH(CDBException,ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException,e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
	END_CATCH;
	
	//Ϊ���������ֵ
	CString sql,tempGroupName;
	CRecordset rs2;
	rs2.m_pDatabase=&m_db;
	if(m_strCurUser=="")
	{
		sql.Format("select * from contact_group");
	}
	else
	{
		sql.Format("select * from contact_group where group_id in(select group_id from user_own where user_id=%d)",GetCurUserID());
	}
	rs2.Open(CRecordset::dynaset,sql);
	while(!rs2.IsEOF())
	{
		rs2.GetFieldValue(1,tempGroupName);
		dlg.m_strAllGroupArr.Add(tempGroupName);
		rs2.MoveNext();
	}
	rs2.Close();
	
	//����ϵ�˶Ի�������޸�
	if(dlg.DoModal()==IDOK)
	{
		//�ӶԻ����л�ȡ������Email����
		CString strName=dlg.m_strCName;
		CString strEmail=dlg.m_strCEmail;

		if(""==strName || ""==strEmail)
		{
			MessageBox("�������ʼ���ַ����Ϊ��","��ʾ");
			return;
		}

		TRY
		{
			CString sql;
			
			//����Ҫ��ӵ����id
			int tempGroupID=0;
			CRecordset rs(&m_db);
			sql.Format("select * from contact_group where group_name='%s'",dlg.m_strContactGroup);
			rs.Open(CRecordset::dynaset,sql);
			if(!rs.IsEOF())
			{
				CDBVariant var;
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					tempGroupID=var.m_iVal;
				}
			}
			rs.Close();
			
			if(0==tempGroupID)
			{
				MessageBox("�˷��鲢�����ڣ�����֮��","��ʾ");
				return;
			}

			//�޸����ݿ���Ӧ�ļ�¼
			sql.Format("update contact_info_tab set contact_name='%s',e_mail='%s',GROUP_ID=%d,HEAD_PIC_PATH='%s' where contact_id=%d",strName,strEmail,tempGroupID,dlg.m_strHeadPath,id);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
			//�޸��б�ؼ���ֵ
			m_listContact.SetItemText(cItem,1,strName);
			m_listContact.SetItemText(cItem,2,strEmail);
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}
}

void CEmailManagementDlg::OnBtnAddtype() 
{
	//����һ�����ͶԻ���ʵ��
	CEmailTypeDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		//�ӶԻ����л�ȡEmail���Ͳ���
		CString strEmailType=dlg.m_strEmailType;
		TRY
		{
			//�򿪼�¼��
			CRecordset rs(&m_db);
			rs.Open(CRecordset::dynaset,"select max(type_id) from email_type_tab");
			//��������Ӽ�¼����ϵ�˵�IDֵ
			int newTypeID=1;
			//������ݿ������м�¼�ˣ����µ���ϵ��ID=��ϵ�˵�ID���ֵ��1
			if(!rs.IsEOF())
			{
				CDBVariant var;
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					newTypeID=var.m_iVal+1;
				}
			}
			//������������ϵ�˼�¼���ַ���
			CString sql;
			sql.Format("insert into email_type_tab(type_id,TYPE_NAME) values(%d,'%s')",newTypeID,strEmailType);
			TRACE(sql);
			//�µ��ʼ����ͼ�¼���뵽���ݿ���
			m_db.ExecuteSQL(sql);
			//���µ��ʼ����ͼ�¼����Ϣ��ʾ���б�ؼ���
			ReadTypeInfo(newTypeID,strEmailType);
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}	
}

void CEmailManagementDlg::OnBtnDeltype() 
{
	//��ȡҪɾ�����ʼ����͵ļ�¼���ڵ���
	int cItem=m_listType.GetNextItem(-1,LVNI_SELECTED);
	if(cItem==-1)
	{
		AfxMessageBox("û��ѡ��Ҫɾ������ϵ�ˣ�");
		return;
	}
	//���Ҫɾ������ϵ�˵�id
	int id=atoi(m_listType.GetItemText(cItem,0));
	TRY
	{
		CString sql;
		//�����ݿ���ɾ����¼
		sql.Format("delete email_type_tab where TYPE_ID=%d",id);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		//���б�ؼ���ɾ���ü�¼
		m_listType.DeleteItem(cItem);
	}
	CATCH(CDBException,ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException,e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
	END_CATCH;
}

//ɾ��һ������
void CEmailManagementDlg::OnBtnGroupDel() 
{
	//��ȡҪɾ�����ʼ����͵ļ�¼���ڵ���
	int cItem=m_listGroup.GetNextItem(-1,LVNI_SELECTED);
	if(cItem==-1)
	{
		AfxMessageBox("û��ѡ��Ҫɾ������ϵ�ˣ�");
		return;
	}
	//���Ҫɾ�������id
	int groupID=atoi(m_listGroup.GetItemText(cItem,0));
	if(MessageBox("��ȷ��Ҫɾ����ϵ����","��ʾ",MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	TRY
	{
		CString sql;
		
		//�к���ʾ
		if(MessageBox("ɾ��������ܻ��漰���޸���ϵ����Ϣ����ȷ����","��ʾ")!=IDOK)
		{
			GetDlgItem(IDC_LIST_GROUP)->SetFocus();
			return;
		}
		
		//�޸���ϵ���б��е�groupID;
		sql.Format("update contact_info_tab set GROUP_ID=null where GROUP_ID=%d",groupID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		
		//�����ݿ���ɾ����¼
		sql.Format("delete contact_group where GROUP_ID=%d",groupID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		if(m_strCurUser!="")
		{
			sql.Format("delete user_own where GROUP_ID=%d",groupID);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
		}
		//���б�ؼ���ɾ���ü�¼
		m_listGroup.DeleteItem(cItem);
		GetCurUserIdInfo();
		CurUserChangeInit();
	}
	CATCH(CDBException,ex)
	{
		AfxMessageBox(ex->m_strError);
		AfxMessageBox(ex->m_strStateNativeOrigin);
	}
	AND_CATCH(CException,e)
	{
		TCHAR szError[100];
		e->GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
	END_CATCH;		
}

void CEmailManagementDlg::OnBtnModtype() 
{
	//ѡ��Ҫ�޸ĵļ�¼��
	int cItem=m_listType.GetNextItem(-1,LVNI_SELECTED);
	if(cItem==-1)
	{
		AfxMessageBox("û��ѡ��Ҫ�޸ĵ���ϵ�ˣ�");
		return;
	}
	//��õ�cItem���е���Ϣ
	int id=atoi(m_listType.GetItemText(cItem,0));
	CString strEmailType=m_listType.GetItemText(cItem,1);
	//������ϵ�˶Ի���ʵ��
	CEmailTypeDlg dlg;
	dlg.m_strEmailType=strEmailType;
	//����ϵ�˶Ի�������޸�
	if(dlg.DoModal()==IDOK)
	{
		//�ӶԻ����л�ȡ������Email���Ͳ���
		CString strEmailType=dlg.m_strEmailType;
		TRY
		{
			CString sql;
			//�޸����ݿ���Ӧ�ļ�¼
			sql.Format("update email_type_tab set TYPE_NAME='%s' where TYPE_ID=%d",strEmailType,id);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
			//�޸��б�ؼ���ֵ
			m_listType.SetItemText(cItem,1,strEmailType);
		}
		CATCH(CDBException,ex)
		{
			AfxMessageBox(ex->m_strError);
			AfxMessageBox(ex->m_strStateNativeOrigin);
		}
		AND_CATCH(CException,e)
		{
			TCHAR szError[100];
			e->GetErrorMessage(szError,100);
			AfxMessageBox(szError);
		}
		END_CATCH;
	}		
}

//������е��б�ؼ�
void CEmailManagementDlg::ClearAllLists()
{
	m_listContact.DeleteAllItems();
	m_listRecord.DeleteAllItems();
	m_listType.DeleteAllItems();
	m_listGroup.DeleteAllItems();
	m_listFujian.DeleteAllItems();
	m_listRecycleBin.DeleteAllItems();
	m_listBlack.DeleteAllItems();
}

//���ʼ������б�ؼ���ȫ�����
void CEmailManagementDlg::ClearAllListsUnless()
{
	m_listContact.DeleteAllItems();
	m_listRecord.DeleteAllItems();
	m_listGroup.DeleteAllItems();
	m_listFujian.DeleteAllItems();
	m_listRecycleBin.DeleteAllItems();
	m_listBlack.DeleteAllItems();
}

void CEmailManagementDlg::InitListControl()
{
	//�����б�ؼ�����չ���
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_listContact.SetExtendedStyle(dwExStyle);
	m_listRecord.SetExtendedStyle(dwExStyle);
	m_listType.SetExtendedStyle(dwExStyle);
	m_listGroup.SetExtendedStyle(dwExStyle);
	m_listFujian.SetExtendedStyle(dwExStyle);
	m_listRecycleBin.SetExtendedStyle(dwExStyle);
	m_listBlack.SetExtendedStyle(dwExStyle);
	
	//��ʼ����ϵ���б�ؼ�
	m_listContact.InsertColumn(0,"ID",LVCFMT_CENTER,30);
	m_listContact.InsertColumn(1,"����",LVCFMT_CENTER,70);
	m_listContact.InsertColumn(2,"E-mail",LVCFMT_CENTER,80);
	m_listContact.InsertColumn(3,"������",LVCFMT_CENTER,100);
	
	//��ʼ���ʼ���¼�б�ؼ�
	m_listRecord.InsertColumn(0,"��¼ ID",LVCFMT_CENTER,60);
	m_listRecord.InsertColumn(1,"����",LVCFMT_CENTER,60);
	m_listRecord.InsertColumn(2,"�ʼ���������",LVCFMT_CENTER,140);
	m_listRecord.InsertColumn(3,"��Ӹ���",LVCFMT_CENTER,60);
	m_listRecord.InsertColumn(4,"�ʼ�����",LVCFMT_CENTER,60);
	m_listRecord.InsertColumn(5,"�ʼ�����",LVCFMT_CENTER,200);
	m_listRecord.InsertColumn(6,"������",LVCFMT_CENTER,140);
	
	//��ʼ���ʼ������б�ؼ�
	m_listType.InsertColumn(0,"���� ID",LVCFMT_CENTER,60);
	m_listType.InsertColumn(1,"�ʼ�����",LVCFMT_CENTER,100);
	
	//��ʼ����ϵ�˷����б�ؼ�
	m_listGroup.InsertColumn(0,"�� ID",LVCFMT_CENTER,55);
	m_listGroup.InsertColumn(1,"����",LVCFMT_CENTER,55);
	m_listGroup.InsertColumn(2,"�鱸ע",LVCFMT_CENTER,55);
	
	//��ʼ�����������б�ؼ�
	m_listFujian.InsertColumn(0,"����ID",LVCFMT_CENTER,55);
	m_listFujian.InsertColumn(1,"������",LVCFMT_CENTER,50);
	m_listFujian.InsertColumn(2,"��������",LVCFMT_CENTER,60);
	
	//��ʼ������վ�б�ؼ�
	m_listRecycleBin.InsertColumn(0,"��¼ ID",LVCFMT_CENTER,60);
	m_listRecycleBin.InsertColumn(1,"����",LVCFMT_CENTER,60);
	m_listRecycleBin.InsertColumn(2,"�ʼ���������",LVCFMT_CENTER,140);
	m_listRecycleBin.InsertColumn(3,"��Ӹ���",LVCFMT_CENTER,60);
	m_listRecycleBin.InsertColumn(4,"�ʼ�����",LVCFMT_CENTER,60);
	m_listRecycleBin.InsertColumn(5,"�ʼ�����",LVCFMT_CENTER,200);
	m_listRecycleBin.InsertColumn(6,"������",LVCFMT_CENTER,140);
	
	//��ʼ���������б�ؼ�
	m_listBlack.InsertColumn(0,"ID",LVCFMT_CENTER,60);
	m_listBlack.InsertColumn(1,"����",LVCFMT_CENTER,60);
	m_listBlack.InsertColumn(2,"E-mail",LVCFMT_CENTER,60);
}

//�鿴�Ѷ��ʼ��ĺ�����Ӧ
void CEmailManagementDlg::OnBtnReaded() 
{
	m_listRecord.DeleteAllItems();
	CString sql;
	if(m_strCurUser=="")
	{
		sql="select * from view_email_readed";
	}
	else
	{
		sql.Format("select * from view_email_readed where record_id in (select record_id from user_own where user_id=%d)",\
			GetCurUserID());
	}
	ReadReadedOrNotEmail(sql);
}

//�ο�δ���ʼ��ĺ�����Ӧ
void CEmailManagementDlg::OnBtnNotread() 
{
	m_listRecord.DeleteAllItems();
	CString sql;
	if(m_strCurUser=="")
	{
		sql="select * from view_email_notread";
	}
	else
	{
		sql.Format("select * from view_email_notread where record_id in (select record_id from user_own where user_id=%d)",\
			GetCurUserID());
	}
	ReadReadedOrNotEmail(sql);
}

//����ѯ�Ѷ�δ���ʼ���ʹ�õĺ���
void CEmailManagementDlg::ReadReadedOrNotEmail(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		
		rs.Open(CRecordset::dynaset,sql);
		int id,isFujian;
		CString contactName,sendDate,typeName,emailInfo,fujianName;
		
		while(!rs.IsEOF())
		{
			id=-1;	isFujian=-1;
			contactName="";		sendDate="";	typeName="";	emailInfo="";	fujianName="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				id=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,contactName);
			rs.GetFieldValue(2,sendDate);
			rs.GetFieldValue((short)3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				isFujian=var.m_iVal;
			var.Clear();
			rs.GetFieldValue(4,typeName);
			rs.GetFieldValue(5,emailInfo);
			rs.GetFieldValue(6,fujianName);
			ReadRecordInfo(id,contactName,sendDate,isFujian,typeName,emailInfo,fujianName);
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

//��ʼ���ʼ������б�ؼ�������
void CEmailManagementDlg::InitEmailTypeData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		int id;
		CString typeName;
		
		//���ʼ������б�ؼ�������ʼ�������Ϣ
		sql="select * from email_type_tab";
		//��ȡ�ʼ����͵ļ�¼��
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			CDBVariant var;
			//��ȡ�ʼ�����id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				id=var.m_iVal;
			var.Clear();
			//��ȡ�ʼ����������ֶ�ֵ
			rs.GetFieldValue(1,typeName);
			//���ʼ������б�ؼ��м����µļ�¼��Ϣ
			ReadTypeInfo(id,typeName);
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

//��ʼ����ϵ����Ϣ�б�ؼ�������(����)
void CEmailManagementDlg::InitContactListData(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		/*CString sql;*/
		
		//�����ϵ�˻�����¼��Ϣ
		/*sql="select * from contact_info_tab where IS_BLACK=0 or IS_BLACK is null";*/
		//��ȡ�ʼ���ϵ�˵ļ�¼��
		rs.Open(CRecordset::dynaset,sql);
		int id,groupID;
		CString name,email,TempGroup;
		while(!rs.IsEOF())
		{
			groupID=-1;
			TempGroup="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				id=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,name);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,email);
			//��ȡ��ϵ���������id;
			rs.GetFieldValue((short)3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
			{
				groupID=var.m_iVal;
			}
			else
			{
				groupID=NULL;
			}
			var.Clear();
			
			CRecordset rs2(&m_db);
			CString sql2;
			sql2.Format("select * from contact_group where group_id=%d",groupID);
			rs2.Open(CRecordset::dynaset,sql2);
			while(!rs2.IsEOF())
			{
				rs2.GetFieldValue(1,TempGroup);
				rs2.MoveNext();
			}
			rs2.Close();
			
			//�Ѽ�¼ֽ���뵽��ϵ���б�ؼ���
			ReadcontactInfo(id,name,email,TempGroup);
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


//��ʼ����ϵ����Ϣ�б�ؼ�������
void CEmailManagementDlg::InitContactListData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//�����ϵ�˻�����¼��Ϣ
		sql="select * from contact_info_tab where IS_BLACK=0 or IS_BLACK is null";
		//��ȡ�ʼ���ϵ�˵ļ�¼��
		rs.Open(CRecordset::dynaset,sql);
		int id,groupID;
		CString name,email,TempGroup;
		while(!rs.IsEOF())
		{
			groupID=-1;
			TempGroup="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				id=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,name);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,email);
			//��ȡ��ϵ���������id;
			rs.GetFieldValue((short)3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
			{
				groupID=var.m_iVal;
			}
			else
			{
				groupID=NULL;
			}
			var.Clear();
			
			CRecordset rs2(&m_db);
			CString sql2;
			sql2.Format("select * from contact_group where group_id=%d",groupID);
			rs2.Open(CRecordset::dynaset,sql2);
			while(!rs2.IsEOF())
			{
				rs2.GetFieldValue(1,TempGroup);
				rs2.MoveNext();
			}
			rs2.Close();
			
			//�Ѽ�¼ֽ���뵽��ϵ���б�ؼ���
			ReadcontactInfo(id,name,email,TempGroup);
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

//��ʼ����ϵ�˷����б�ؼ�������(����)
void CEmailManagementDlg::InitContactGroupData(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		
		rs.Open(CRecordset::dynaset,sql);
		int groupid;
		CString groupname,groupDesc;
		while(!rs.IsEOF())
		{
			groupid=-1;
			groupname="";	groupDesc="";
			CDBVariant var;
			//��ȡ��ϵ����id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				groupid=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,groupname);
			//��ȡ��ϵ���鱸ע
			rs.GetFieldValue(2,groupDesc);
			ReadContactGroupInfo(groupid,groupname,groupDesc);
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


//��ʼ����ϵ�˷����б�ؼ�������
void CEmailManagementDlg::InitContactGroupData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//����ϵ�˷����б�ؼ��������Ϣ
		sql.Format("select * from contact_group");
		rs.Open(CRecordset::dynaset,sql);
		int groupid;
		CString groupname,groupDesc;
		while(!rs.IsEOF())
		{
			CDBVariant var;
			//��ȡ��ϵ����id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				groupid=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,groupname);
			//��ȡ��ϵ���鱸ע
			rs.GetFieldValue(2,groupDesc);
			ReadContactGroupInfo(groupid,groupname,groupDesc);
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

//��ʼ������վ�б�ؼ�������(����)
void CEmailManagementDlg::InitRecycleBinData(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		
		rs.Open(CRecordset::dynaset,sql);
		int tempRecordID,tempIsFujian;
		CString huishouName,huishouDate,huishouType,huishouInfo,huishouFujian;
		while(!rs.IsEOF())
		{
			tempRecordID=-1;tempIsFujian=-1;
			huishouName="";huishouDate="";huishouType="";huishouInfo="";huishouFujian="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				tempRecordID=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,huishouName);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,huishouDate);
			//��ȡ��ϵ���������id;
			rs.GetFieldValue((short)3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
			{
				tempIsFujian=var.m_iVal;
			}
			var.Clear();
			rs.GetFieldValue(4,huishouType);
			rs.GetFieldValue(5,huishouInfo);
			rs.GetFieldValue(6,huishouFujian);
			
			//�Ѽ�¼���뵽����վ�б�ؼ���
			ReadRecycleBinInfo(tempRecordID,huishouName,huishouDate,tempIsFujian,huishouType,huishouInfo,huishouFujian);
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


//��ʼ������վ�б�ؼ�������
void CEmailManagementDlg::InitRecycleBinData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//��ʼ������վ�б�ؼ�
		sql="select * from view_record_recycle_bin";
		rs.Open(CRecordset::dynaset,sql);
		int tempRecordID,tempIsFujian;
		CString huishouName,huishouDate,huishouType,huishouInfo,huishouFujian;
		while(!rs.IsEOF())
		{
			tempRecordID=-1;tempIsFujian=-1;
			huishouName="";huishouDate="";huishouType="";huishouInfo="";huishouFujian="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				tempRecordID=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,huishouName);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,huishouDate);
			//��ȡ��ϵ���������id;
			rs.GetFieldValue((short)3,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
			{
				tempIsFujian=var.m_iVal;
			}
			var.Clear();
			rs.GetFieldValue(4,huishouType);
			rs.GetFieldValue(5,huishouInfo);
			rs.GetFieldValue(6,huishouFujian);
			
			//�Ѽ�¼���뵽����վ�б�ؼ���
			ReadRecycleBinInfo(tempRecordID,huishouName,huishouDate,tempIsFujian,huishouType,huishouInfo,huishouFujian);
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

//��ʼ���ʼ���¼�б�ؼ�������(����)
void CEmailManagementDlg::InitEmailRecordInfo(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		/*CString sql;
		
		  //���ʼ���¼�б�ؼ�������ʼ�������Ϣ
		sql="select * from email_record_tab where IS_RECYCLE_BIN=0 or IS_RECYCLE_BIN is null";*/
		//��ȡ�ʼ����͵ļ�¼��
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
			
			CRecordset rs2(&m_db);
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
			ReadRecordInfo(recordID,strName,sendDate,isFujian,strType,emailTxt,fujianName);
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

//��ʼ���ʼ���¼�б�ؼ�������
void CEmailManagementDlg::InitEmailRecordInfo()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//���ʼ���¼�б�ؼ�������ʼ�������Ϣ
		sql="select * from email_record_tab where IS_RECYCLE_BIN=0 or IS_RECYCLE_BIN is null";
		//��ȡ�ʼ����͵ļ�¼��
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
			
			CRecordset rs2(&m_db);
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
			ReadRecordInfo(recordID,strName,sendDate,isFujian,strType,emailTxt,fujianName);
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

//��ʼ���������б�ؼ�������(����)
void CEmailManagementDlg::InitBlackListData(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		
		rs.Open(CRecordset::dynaset,sql);
		int blackID;
		CString blackName,blackEmail;
		
		while(!rs.IsEOF())
		{
			blackID=-1;
			blackName="";blackEmail="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				blackID=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,blackName);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,blackEmail);
			
			//�Ѽ�¼���뵽����վ�б�ؼ���
			ReadBlackListInfo(blackID,blackName,blackEmail);
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


//��ʼ���������б�ؼ�������
void CEmailManagementDlg::InitBlackListData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//��ʼ������վ�б�ؼ�
		sql="select * from view_black_list";
		rs.Open(CRecordset::dynaset,sql);
		int blackID;
		CString blackName,blackEmail;
		
		while(!rs.IsEOF())
		{
			blackID=-1;
			blackName="";blackEmail="";
			
			CDBVariant var;
			//��ȡ��ϵ��id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				blackID=var.m_iVal;
			var.Clear();
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(1,blackName);
			//��ȡ��ϵ�������ֶ�ֵ
			rs.GetFieldValue(2,blackEmail);
			
			//�Ѽ�¼���뵽����վ�б�ؼ���
			ReadBlackListInfo(blackID,blackName,blackEmail);
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

//��ʼ�������б�ؼ�������(����)
void CEmailManagementDlg::InitFujianListData(CString sql)
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		/*	CString sql;
		
		  //�򸽼������б��г�ʼ��ֵ
		sql="select * from email_fujian where fid>0";*/
		rs.Open(CRecordset::dynaset,sql);
		int fujianID;
		CString fujianName,fujianDesc;
		while(!rs.IsEOF())
		{
			fujianID=-1;
			fujianName="";
			fujianDesc="";
			
			CDBVariant var;
			//��ȡ����id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				fujianID=var.m_iVal;
			var.Clear();
			if(-1==fujianID)
			{
				break;
			}
			//��ȡ�������ֶ�ֵ
			rs.GetFieldValue(1,fujianName);
			//��ȡ������ע
			rs.GetFieldValue(2,fujianDesc);
			ReadFujianInfo(fujianID,fujianName,fujianDesc);
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


//��ʼ�������б�ؼ�������
void CEmailManagementDlg::InitFujianListData()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//�򸽼������б��г�ʼ��ֵ
		sql="select * from email_fujian where fid>0";
		rs.Open(CRecordset::dynaset,sql);
		int fujianID;
		CString fujianName,fujianDesc;
		while(!rs.IsEOF())
		{
			fujianID=-1;
			fujianName="";
			fujianDesc="";
			
			CDBVariant var;
			//��ȡ����id�ֶ�ֵ
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType != DBVT_NULL)
				fujianID=var.m_iVal;
			var.Clear();
			//��ȡ�������ֶ�ֵ
			rs.GetFieldValue(1,fujianName);
			//��ȡ������ע
			rs.GetFieldValue(2,fujianDesc);
			ReadFujianInfo(fujianID,fujianName,fujianDesc);
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



//��ʼ�������б�ؼ�������
void CEmailManagementDlg::InitListData()
{
	//��ʼ���ʼ������б�ؼ�
	InitEmailTypeData();
	
	//��ʼ����ϵ����Ϣ�б�ؼ�������
	InitContactListData();
	
	//��ʼ����ϵ�˷����б�ؼ�������
	InitContactGroupData();
	
	//��ʼ������վ�б�ؼ�������
	InitRecycleBinData();
	
	//��ʼ���ʼ���¼�б�ؼ�������
	InitEmailRecordInfo();
	
	//��ʼ���������б�ؼ�������
    InitBlackListData();
	
	//��ʼ�������б�ؼ�������
	InitFujianListData();
	
	//����������ť�Ŀ���
	GetDlgItem(IDC_BTN_ADDTYPE)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MODTYPE)->EnableWindow(true);
	GetDlgItem(IDC_BTN_DELTYPE)->EnableWindow(true);
}

//��Ӻ������б�ؼ���Ϣ�ĺ���ʵ��
void CEmailManagementDlg::ReadBlackListInfo(int blackID, CString blackName, CString blackEmail)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listBlack.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",blackID);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_listBlack.InsertItem(&lvItem);
	m_listBlack.SetItemText(nIndex,1,blackName);
	m_listBlack.SetItemText(nIndex,2,blackEmail);
}


//�����ϵ���б�ؼ���Ϣ�ĺ���ʵ��
void CEmailManagementDlg::ReadcontactInfo(int id, CString name, CString email,CString group)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listContact.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",id);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_listContact.InsertItem(&lvItem);
	m_listContact.SetItemText(nIndex,1,name);
	m_listContact.SetItemText(nIndex,2,email);
	m_listContact.SetItemText(nIndex,3,group);
}

//����ʼ������б�ؼ���Ϣ�ĺ���ʵ��
void CEmailManagementDlg::ReadTypeInfo(int id, CString typeName)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listType.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",id);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_listType.InsertItem(&lvItem);
	m_listType.SetItemText(nIndex,1,typeName);
}

//�򸽼������б�ؼ������Ϣ�ĺ���
void CEmailManagementDlg::ReadFujianInfo(int id, CString fujianName, CString fujianDesc)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listFujian.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",id);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_listFujian.InsertItem(&lvItem);
	m_listFujian.SetItemText(nIndex,1,fujianName);
	m_listFujian.SetItemText(nIndex,2,fujianDesc);
}

//�����ϵ�˷����б�ؼ���Ϣ�ĺ���ʵ��
void CEmailManagementDlg::ReadContactGroupInfo(int id, CString groupName, CString groupDesc)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_listGroup.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",id);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	
	//����һ������
	m_listGroup.InsertItem(&lvItem);
	m_listGroup.SetItemText(nIndex,1,groupName);
	m_listGroup.SetItemText(nIndex,2,groupDesc);
}

//���ʼ���¼�б�����Ӽ�¼
void CEmailManagementDlg::ReadRecordInfo(int id, CString name, CString sendDate, int isFujian, CString type, CString emailTxt,CString fujianName)
{
	ReadRecordInfo(m_listRecord,id,name,sendDate,isFujian,type,emailTxt,fujianName);
}

void CEmailManagementDlg::ReadRecycleBinInfo(int id, CString name, CString sendDate, int isFujian, CString type, CString emailTxt, CString fujianName)
{
	ReadRecordInfo(m_listRecycleBin,id,name,sendDate,isFujian,type,emailTxt,fujianName);
}

//���ڳ�ʼ���ʼ���¼�б�ؼ��ͻ���վ�б�ؼ�
void CEmailManagementDlg::ReadRecordInfo(CListCtrl &m_list, int id, CString name, CString sendDate, int isFujian, CString type, CString emailTxt, CString fujianName)
{
	//��õ�ǰ�ļ�¼��
	int nIndex=m_list.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask=LVIF_TEXT;
	lvItem.iItem=nIndex;
	lvItem.iSubItem=0;
	CString temp;
	temp.Format("%d",id);
	lvItem.pszText=(char *)(LPCTSTR)temp;
	//��nIndexһ�в�����ϵ����Ϣ����
	m_list.InsertItem(&lvItem);
	m_list.SetItemText(nIndex,1,name);
	m_list.SetItemText(nIndex,2,sendDate);
	m_list.SetItemText(nIndex,3,isFujian==0?"��":"��");
	m_list.SetItemText(nIndex,4,type);
	m_list.SetItemText(nIndex,5,emailTxt);
	m_list.SetItemText(nIndex,6,fujianName);
}

void CEmailManagementDlg::OnBtnSendred() 
{
	//��ʼ���ʼ���¼��Ϣ�Ի���
	CEmailRecordDlg dlg;
	//��ȡ������ϵ�˵�����
	int n=m_listContact.GetItemCount();
	for(int i=0;i<n;i++)
	{
		CString mytempname=m_listContact.GetItemText(i,1);
		dlg.m_strContactArray.Add(mytempname);
	}
	//��ȡ�����ʼ�������Ϣ
	for(i=0;i<m_listType.GetItemCount();i++)
	{
		dlg.m_strTypeArray.Add(m_listType.GetItemText(i,1));
	}
	//��ȡ�����������
	for(i=0;i<m_listGroup.GetItemCount();i++)
	{
		dlg.m_strGroupArr.Add(m_listGroup.GetItemText(i,1));
	}
	//���ʼ���¼�Ի�������µļ�¼
	if(IDOK==dlg.DoModal())
	{
		CString strName,strType,strSendDate,strEInfo,strFujianName,strFujianDesc;
		int isFujian,isDraft;
		
		if(dlg.m_isQunfa==false)
		{
			dlg.m_strReceiverArr.Add(dlg.m_strContact);
		}
		for(int i=0;i<dlg.m_strReceiverArr.GetSize();i++)
		{
			//�ӶԻ����л�ȡ��¼ֵ
			strName=dlg.m_strReceiverArr.GetAt(i);
			strType=dlg.m_strEtype;
			strSendDate=COleDateTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");
			isFujian=dlg.m_isFujian;
			strEInfo=dlg.m_strEmailInfo;
			strFujianName=dlg.m_strFileName;
			strFujianDesc=dlg.m_strFujianDesc;
			isDraft=dlg.m_isDraft;
			
			if(""==strEInfo)
			{
				MessageBox("�ʼ����ݲ���Ϊ��","��ʾ");
				break;
			}
			if(1==isFujian && ""==strFujianName)
			{
				MessageBox("�������Ʋ���Ϊ��","��ʾ");
				break;
			}
            if(""==strType)
			{
				MessageBox("�ʼ����Ͳ���Ϊ��","��ʾ");
				break;
			}
			if(""==strName)
			{
				MessageBox("��ϵ����������Ϊ��","��ʾ");
				break;
			}
			
			TRY
			{
				CRecordset rs(&m_db);
				CString sql;
				//������ϵ��������ȡ��ϵ��IDֵ
				sql.Format("select contact_id from contact_info_tab where contact_name='%s'",strName);
				rs.Open(CRecordset::dynaset,sql);
				int contactID=-1;
				if(!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var,SQL_C_SLONG);
					if(var.m_dwType!=DBVT_NULL)
					{
						contactID=var.m_iVal;
					}
				}
				rs.Close();
				
				//�����ϵ�˲����ڣ������
				if(-1==contactID)
				{
					if(IDOK==MessageBox("����ϵ�˲����ڣ��������Ƿ���ӣ�","��ʾ"))
					{
						OnBtnAddcon();
						
						sql.Format("select contact_id from contact_info_tab where contact_name='%s'",strName);
						rs.Open(CRecordset::dynaset,sql);
						if(!rs.IsEOF())
						{
							CDBVariant var;
							rs.GetFieldValue((short)0,var,SQL_C_SLONG);
							if(var.m_dwType!=DBVT_NULL)
							{
								contactID=var.m_iVal;
							}
						}
						rs.Close();
						
						if(-1==contactID)
						{
							MessageBox("���������ϵ��ǰ��һ��!����֮����ϵ���Ѿ�Ϊ����ӣ��ʼ���δ����","����");
							return ;
						}
					}
					else
					{
						return;
					}
				}
				
				//�����ʼ����ͻ�ȡ�ʼ�����ID
				sql.Format("select type_id from email_type_tab where type_name='%s'",strType);
				rs.Open(CRecordset::dynaset,sql);
				int typeID=1;
				if(!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var,SQL_C_SLONG);
					if(var.m_dwType!=DBVT_NULL)
					{
						typeID=var.m_iVal;
					}
				}
				rs.Close();
				
				//�򸽼����в���һ������
				int tempFujianID;
				
				if(isFujian==1)
				{
					int sk=0;
					sql.Format("select * from email_fujian where fname='%s'",strFujianName);
					rs.Open(CRecordset::snapshot,sql);
					if(!rs.IsEOF())
					{
						CDBVariant var;
						rs.GetFieldValue((short)0,var,SQL_C_SLONG);
						if(var.m_dwType!=DBVT_NULL)
						{
							sk=var.m_iVal;
						}
					}
					rs.Close();
					
					if(0!=sk)
					{
						MessageBox("������������ͬ����������ĸ��������ϴ�");
						return;
					}
					
					if(strFujianName!="")
					{
						sql.Format("call email_load_fujian('%s','%s')",strFujianName,strFujianDesc);
						TRACE(sql);
						m_db.ExecuteSQL(sql);
					}
					else
					{
						MessageBox("����������Ϊ��","����������ʾ");
						return;
					}
					
					//��ȡ������ID
					sql.Format("select fid from email_fujian where fname='%s'",strFujianName);
					rs.Open(CRecordset::snapshot,sql);
					if(!rs.IsEOF())
					{
						CDBVariant var;
						rs.GetFieldValue((short)0,var,SQL_C_SLONG);
						if(var.m_dwType!=DBVT_NULL)
						{
							tempFujianID=var.m_iVal;
						}
					}
					rs.Close();
					
					ReadFujianInfo(tempFujianID,strFujianName,strFujianDesc);
				}
				else
				{
					tempFujianID=0;
				}
				
				
				//��SEQ_RECORD_ID�����л�ȡ��һ��ֵ
				rs.Open(CRecordset::snapshot,"select SEQUENCE_RECORD_ID.NEXTVAL from dual");
				int recordID=10000;
				if(!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var,SQL_C_SLONG);
					if(var.m_dwType!=DBVT_NULL)
					{
						recordID=var.m_iVal;
					}
				}
				
				//�����¼�¼
				if(isFujian==1)
				{
					sql.Format("insert into email_record_tab(record_id,contact_id,send_date,is_fujian,\
																									type_id,email_info,fujian_id,isread,IS_RECYCLE_BIN,is_draft) values(%d,%d,to_date('%s','yyyy-mm-dd hh24:mi:ss'),\
																									%d,%d,'%s',%d,%d,%d,%d)",recordID,
																									contactID,strSendDate,isFujian,typeID,strEInfo,tempFujianID,0,0,isDraft);
					TRACE(sql);
					m_db.ExecuteSQL(sql);
					rs.Close();
					if(1!=isDraft)
					{
						//���������в����µļ�¼
						ReadRecordInfo(recordID,strName,strSendDate,isFujian,strType,strEInfo,strFujianName);
					}
					else
					{
						MessageBox("���Ѿ����˷��ʼ���Ϊ�ݸ�");
					}
					if(m_strCurUser!="")
					{
						sql.Format("insert into user_own(USER_ID,CONTACT_ID,RECORD_ID,GROUP_ID,FUJIAN_ID) values(%d,%d,%d,%d,%d)",\
							GetCurUserID(),contactID,recordID,0,tempFujianID);
						TRACE(sql);
						m_db.ExecuteSQL(sql);
					}
				}
				else
				{
					sql.Format("insert into email_record_tab(record_id,contact_id,send_date,is_fujian,type_id,\
						email_info,isread,IS_RECYCLE_BIN,is_draft) values(%d,%d,to_date('%s','yyyy-mm-dd hh24:mi:ss'),%d,%d,\
						'%s',%d,%d,%d)",\
						recordID,
						contactID,strSendDate,isFujian,typeID,strEInfo,0,0,isDraft);
					TRACE(sql);
					m_db.ExecuteSQL(sql);
					rs.Close();
					if(1!=isDraft)
					{
						ReadRecordInfo(recordID,strName,strSendDate,isFujian,strType,strEInfo,"");
					}
					else
					{
						MessageBox("���Ѿ����˷��ʼ���Ϊ�ݸ�");
					}
					if(m_strCurUser!="")
					{
						sql.Format("insert into user_own(USER_ID,CONTACT_ID,RECORD_ID,GROUP_ID,FUJIAN_ID) values(%d,%d,%d,%d,%d)",\
							GetCurUserID(),contactID,recordID,0,0);
						TRACE(sql);
						m_db.ExecuteSQL(sql);
					}
				}
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
		if(""==strEInfo)
		{
				return;
		}
		if(1==isFujian && ""==strFujianName)
		{
				return;
		}
		if(""==strType)
		{
				return;
		}
		if(""==strName)
		{
				return;
		}
	}	
}

//����ϵ������
void CEmailManagementDlg::OnBtnMovetoBlackList() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listContact.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int contactID=atoi(m_listContact.GetItemText(rItem,0));
	
	TRY
	{
		
		CString sql;
		sql.Format("update contact_info_tab set IS_BLACK=1 where CONTACT_ID=%d",contactID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		m_listContact.DeleteItem(rItem);
		m_listBlack.DeleteAllItems();
		if(m_strCurUser=="")
		{
			InitBlackListData();
		}
		else
		{
			GetCurUserIdInfo();
			CurUserChangeInit();
		}
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

//�Ӻ������л�ԭ
void CEmailManagementDlg::OnBtnReturntoContact() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listBlack.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int contactID=atoi(m_listBlack.GetItemText(rItem,0));
	
	TRY
	{
		CString sql;
		sql.Format("update contact_info_tab set IS_BLACK=0 where CONTACT_ID=%d",contactID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		m_listBlack.DeleteItem(rItem);
		m_listContact.DeleteAllItems();
		if(m_strCurUser=="")
		{
			//��ʼ���ʼ���¼�б�ؼ�������
			InitContactListData();
		}
		else
		{
			CurUserChangeInit();
		}
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

//�ƶ�������վ
void CEmailManagementDlg::OnBtnMovetoBin() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listRecord.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int recordID=atoi(m_listRecord.GetItemText(rItem,0));
	
	TRY
	{
		
		CString sql;
		sql.Format("update email_record_tab set ISREAD=1 where RECORD_ID=%d",recordID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		sql.Format("update email_record_tab set IS_RECYCLE_BIN=1 where RECORD_ID=%d",recordID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		m_listRecord.DeleteItem(rItem);
		m_listRecycleBin.DeleteAllItems();
		if(m_strCurUser=="")
		{
			InitRecycleBinData();
		}
		else if(m_strCurUser!="")
		{
			GetCurUserIdInfo();
			CurUserChangeInit();
		}
		else
		{
			MessageBox("���������������");
		}
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

//�ӻ���վ�л�ԭ
void CEmailManagementDlg::OnBtnRestore() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listRecycleBin.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int recordID=atoi(m_listRecycleBin.GetItemText(rItem,0));
	
	TRY
	{
		CString sql;
		sql.Format("update email_record_tab set IS_RECYCLE_BIN=0 where RECORD_ID=%d",recordID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		m_listRecycleBin.DeleteItem(rItem);
		m_listRecord.DeleteAllItems();
		if(m_strCurUser=="")
		{
			//��ʼ���ʼ���¼�б�ؼ�������
			InitEmailRecordInfo();
		}
		else if(m_strCurUser!="")
		{
			GetCurUserIdInfo();
			CurUserChangeInit();
		}
		else
		{
			MessageBox("���������������");
		}
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

void CEmailManagementDlg::OnBtnQueryred() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listRecord.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int recordID=atoi(m_listRecord.GetItemText(rItem,0));
	
	//��ʼ���ʼ���¼��Ϣ�Ի���
	CEmailRecordDlg* queryDlg=new CEmailRecordDlg();
	queryDlg->GetRecordID(recordID);
	
	//���Ի��򸳲���
	queryDlg->m_strContact=m_listRecord.GetItemText(rItem,1);
	queryDlg->m_strEtype=m_listRecord.GetItemText(rItem,4);
	queryDlg->m_sendDate.ParseDateTime(m_listRecord.GetItemText(rItem,2));
	if(m_listRecord.GetItemText(rItem,3).CompareNoCase("��")==0)
	{
		queryDlg->m_isFujian=1;
		
		//�����ڸ�����ʱ�򣬾�Ҫ���Ի���ĸ������͸���������ֵ
		queryDlg->m_strFileName=m_listRecord.GetItemText(rItem,6);
		
		//��ȡ��������
		TRY
		{
			CString tempFujiandesc;
			
			CRecordset rs;
			rs.m_pDatabase=&m_db;
			
			CString sql;
			sql.Format("select * from email_fujian where fname='%s'",queryDlg->m_strFileName);
			rs.Open(CRecordset::dynaset,sql);
			while(!rs.IsEOF())
			{
				rs.GetFieldValue(2,tempFujiandesc);
				rs.MoveNext();
			}
			rs.Close();
			
			queryDlg->m_strFujianDesc=tempFujiandesc;
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
	else
	{
		queryDlg->m_isFujian=0;
	}
	queryDlg->m_strEmailInfo=m_listRecord.GetItemText(rItem,5);
	
	//��ȡ�ʼ��Ƿ��Ѷ�
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		//��ȡ�ʼ��Ƿ��Ѷ�
		sql.Format("select * from email_record_tab where RECORD_ID=%d",recordID);
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			CDBVariant var;
			rs.GetFieldValue((short)7,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				queryDlg->m_isRead=var.m_iVal;
			}
			rs.MoveNext();
		}
		rs.Close();
		
		//��ȡ��ϵ�����ڵķ���
		sql.Format("select * from contact_group,email_record_tab,\
																   contact_info_tab where contact_group.group_id=contact_info_tab.group_id\
																   and email_record_tab.contact_id=contact_info_tab.contact_id and record_id=%d",\
																   recordID);
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			CString tempGroup;
			rs.GetFieldValue(1,tempGroup);
			queryDlg->m_strGroup=tempGroup;
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
		
		//���ʼ���¼�ĶԻ���
		queryDlg->Create(IDD_DIALOG_RECORD);
	BOOL isShow=queryDlg->ShowWindow(SW_SHOWNORMAL); //��ʾ��ģ̬�Ի���
	
	queryDlg->GetDlgItem(IDC_CHECK_ISREAD)->ShowWindow(true);
	
	if(queryDlg->m_isFujian==1)
	{
		queryDlg->GetDlgItem(IDC_EDIT_FILE_NAME)->ShowWindow(true);
		queryDlg->GetDlgItem(IDC_EDIT_FILE_DESC)->ShowWindow(true);
	}
    if(queryDlg->m_isRead==1)
	{
		queryDlg->GetDlgItem(IDC_CHECK_ISREAD)->EnableWindow(false);
	}
	
	if(isShow)
	{
		//��ȡ�鿴��¼��ֵ
		CString strName=queryDlg->m_strContact;
		CString strType=queryDlg->m_strEtype;
		CString strSendDate=m_listRecord.GetItemText(rItem,2);
		int isFujian=queryDlg->m_isFujian;
		CString strEmailInfo=queryDlg->m_strEmailInfo;
		CString fujianName=queryDlg->m_strFujianDesc;
		TRY
		{
			m_listRecord.DeleteItem(rItem);
			ReadRecordInfo(recordID,strName,strSendDate,isFujian,strType,strEmailInfo,"");
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
}

void CEmailManagementDlg::OnBtndelred() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listRecord.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫɾ���ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int recordID=atoi(m_listRecord.GetItemText(rItem,0));
	
	TRY
	{
		CString sql;
		int fujianID;
		//ɾ����ʱ����ɾ���������еĸ���
		
		//1. ��ȡԪ���¼�ĸ���ID
		sql.Format("select fujian_id from email_record_tab where record_id=%d",recordID);
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		rs.Open(CRecordset::dynaset,sql);
		while(!rs.IsEOF())
		{
			CDBVariant var;
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				fujianID=var.m_iVal;
			}
			rs.MoveNext();
		}
		rs.Close();
		
		//�����ݿ���ɾ����¼
		sql.Format("delete email_record_tab where record_id=%d",recordID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
		
		//2. ɾ�������б��е�Ԫ��
		sql.Format("delete email_fujian where fid=%d",fujianID);
		TRACE(sql);
		m_db.ExecuteSQL(sql);
        if(m_strCurUser!="")
		{
			sql.Format("delete user_own where record_id=%d",recordID);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
			sql.Format("delete user_own where fujian_id=%d",fujianID);
			TRACE(sql);
			m_db.ExecuteSQL(sql);
		}
		//���б�ؼ���ɾ���ü�¼
		m_listRecord.DeleteItem(rItem);
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

void CEmailManagementDlg::OnButtonTimequery() 
{
	TimeQueryDlg dlg;
	CString startTime,endTime;
	if(dlg.DoModal()==IDOK)
	{
		startTime=dlg.m_startDate.Format("%Y-%m-%d");
		endTime=dlg.m_endDate.Format("%Y-%m-%d");
		
		if(startTime>endTime)
		{
			MessageBox("��������ʼʱ�����ֹʱ����ˣ�","������ʾ������");
			return;
		}

		CString sql;
		sql.Format("select RECORD_ID from email_record_tab where to_char(send_date,'yyyy-mm-dd') >= '%s' and to_char(send_date,'yyyy-mm-dd')<='%s'",startTime,endTime);
		int recordID;
		TRY
		{
			CRecordset rs(&m_db);
			rs.Open(CRecordset::dynaset,sql);
			while(!rs.IsEOF())
			{
				CDBVariant var;
				//��ȡidֵ
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					recordID=var.m_iVal;
				}
				var.Clear();
				
				//λѡ�������Ԫ�������ɫ
				for(int nItem=0;nItem<m_listRecord.GetItemCount();nItem++)
				{
					CString strID,strListID;
					strID.Format("%d",recordID);
					strListID=m_listRecord.GetItemText(nItem,0);
					if(strID==strListID)
					{
						m_listRecord.SetFocus();
						m_listRecord.SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
					}
				}
				
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
}

//�ο������ϸ���
void CEmailManagementDlg::OnBtnGroupQuery() 
{
	//��ȡҪ�鿴�ļ�¼��Ϣ���ڵ�����
	int rItem=m_listGroup.GetNextItem(-1,LVNI_SELECTED);
	if(-1==rItem)
	{
		AfxMessageBox("û��ѡ��Ҫ�鿴�ļ�¼");
		return;
	}
	//��ȡ�ʼ���¼ID
	int groupID=atoi(m_listGroup.GetItemText(rItem,0));
	
    //ʵ���������Ի���
	CEmailContactGroupDlg dlg;
	dlg.m_strGroupName=m_listGroup.GetItemText(rItem,1);
	dlg.m_strGroupDesc=m_listGroup.GetItemText(rItem,2);
	dlg.m_AddOrLook=LOOK;
	//�����ݿ��ȡ���ڳ�Ա
	CString strMem;
	
	CRecordset rs;
	rs.m_pDatabase=&m_db;
	CString sql;
	sql.Format("select * from contact_group,contact_info_tab where contact_group.group_id=contact_info_tab.group_id and contact_group.group_id=%d",groupID);	
	rs.Open(CRecordset::dynaset,sql);
	while(!rs.IsEOF())
	{
		rs.GetFieldValue(4,strMem);
		dlg.m_strGroupMemArr.Add(strMem);
		rs.MoveNext();
	}
	rs.Close();
	
	if(IDOK==dlg.DoModal())
	{
		if(MessageBox("����ok��ť�����᳹���޸�ֵ����ȷ����","��ʾ",MB_OKCANCEL)!=IDOK)
		{
			return;
		}
		//��ȡ�鿴��¼��ֵ
		CString strName=dlg.m_strGroupName;
		CString strDesc=dlg.m_strGroupDesc;
		
		TRY
		{
			m_listGroup.DeleteItem(rItem);
			ReadContactGroupInfo(groupID,strName,strDesc);
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
}

//��ȡ���ݿ��ָ��
CDatabase* CEmailManagementDlg::GetDB()
{
	return &m_db;
}

//������ϵ���б�ؼ��ıȽ�
static int m_nlistContactSortColum;
static bool m_bListContactCmp=true;

//�б�ؼ����ڱȽ�
static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort;
    CString   strItem1 = pListCtrl->GetItemText(lParam1,m_nlistContactSortColum);
    CString   strItem2 = pListCtrl->GetItemText(lParam2,m_nlistContactSortColum);    
    if (m_bListContactCmp)
    {    
        return strcmp(strItem2, strItem1);    
    }
    else    
    {
        return strcmp(strItem1, strItem2);    
    }
}

//��ϵ���б�ͷ������
void CEmailManagementDlg::OnColumnclickListContact(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	m_nlistContactSortColum = pNMListView->iSubItem;//�������
	
	int count=m_listContact.GetItemCount();
	for (int i=0;i<count;i++)
	{
		// ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ�����������Ϊ�����ȽϺ����ĵ�һ��������
		m_listContact.SetItemData(i,i); 
	}
	m_listContact.SortItems((PFNLVCOMPARE)MyCompareProc,(LPARAM)&m_listContact);//����ڶ��������ǱȽϺ����ĵ���������
	m_bListContactCmp = !m_bListContactCmp;
	
	*pResult = 0;
}

//�����ʼ������б�ؼ��ıȽ�
static int m_nlistTypeSortColum;
static bool m_bListTypeCmp=true;
//�б�ؼ����ڱȽ�
static int CALLBACK MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort;
    CString   strItem1 = pListCtrl->GetItemText(lParam1,m_nlistTypeSortColum);
    CString   strItem2 = pListCtrl->GetItemText(lParam2,m_nlistTypeSortColum);    
    if (m_bListTypeCmp)
    {    
        return strcmp(strItem2, strItem1);    
    }
    else    
    {
        return strcmp(strItem1, strItem2);    
    }
}
//�ʼ������б�ؼ�
void CEmailManagementDlg::OnColumnclickListEtype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	int count=m_listType.GetItemCount();
	for (int i=0;i<count;i++)
	{
		// ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ�����������Ϊ�����ȽϺ����ĵ�һ��������
		m_listType.SetItemData(i,i); 
	}
	m_listType.SortItems((PFNLVCOMPARE)MyCompareProc1,(LPARAM)&m_listType);//����ڶ��������ǱȽϺ����ĵ���������
	m_bListTypeCmp = !m_bListTypeCmp;
	
	*pResult = 0;
}

//�����ʼ���¼�б�ؼ��ıȽ�
static int m_nlistRecordSortColum;
static bool m_bListRecordCmp=true;
//�б�ؼ����ڱȽ�
static int CALLBACK MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort;
    CString   strItem1 = pListCtrl->GetItemText(lParam1,m_nlistRecordSortColum);
    CString   strItem2 = pListCtrl->GetItemText(lParam2,m_nlistRecordSortColum);    
    if (m_bListRecordCmp)
    {    
        return strcmp(strItem2, strItem1);    
    }
    else    
    {
        return strcmp(strItem1, strItem2);    
    }
}
//�ʼ���¼
void CEmailManagementDlg::OnColumnclickListRecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
    // TODO: Add your control notification handler code here
    m_nlistRecordSortColum = pNMListView->iSubItem; 
	
    m_bListRecordCmp=!m_bListRecordCmp;//�����ǽ���  
    int count = m_listRecord.GetItemCount(); //����    
    for(int i=0; i<count;  i++)      
    {  
        m_listRecord.SetItemData(i,i);      
    }
    m_listRecord.SortItems(MyCompareProc2, (LPARAM) &m_listRecord);
	
	*pResult = 0;
}

//���ڻ���վ�б�ؼ��ıȽ�
static int m_nlistBinSortColum;
static bool m_bListBinCmp=true;
//����վ�б�ؼ����ڱȽ�
static int CALLBACK MyCompareProc3(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort;
    CString   strItem1 = pListCtrl->GetItemText(lParam1,m_nlistBinSortColum);
    CString   strItem2 = pListCtrl->GetItemText(lParam2,m_nlistBinSortColum);    
    if (m_bListBinCmp)
    {    
        return strcmp(strItem2, strItem1);    
    }
    else    
    {
        return strcmp(strItem1, strItem2);    
    }
}
//����վ
void CEmailManagementDlg::OnColumnclickListRecycleBin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	// TODO: Add your control notification handler code here
    m_nlistBinSortColum = pNMListView->iSubItem; 
	
    m_bListBinCmp=!m_bListBinCmp;//�����ǽ���  
    int count = m_listRecycleBin.GetItemCount(); //����    
    for(int i=0; i<count;  i++)      
    {  
        m_listRecycleBin.SetItemData(i,i);      
    }
    m_listRecycleBin.SortItems(MyCompareProc3, (LPARAM) &m_listRecycleBin);
	
	*pResult = 0;
}

//�鿴���ݿ���Ϣ�Ĳ˵���Ӧ
void CEmailManagementDlg::OnDb() 
{
	CDBConnDlg dlg;
	dlg.m_strDBSource=m_strDBSource;
	dlg.m_strUserName=m_strUserName;
	dlg.m_strPassword=m_strPassword;
	if(IDOK==dlg.DoModal())
	{
		m_strDBSource=dlg.m_strDBSource;
		m_strUserName=dlg.m_strUserName;
		m_strPassword=dlg.m_strPassword;
		ConnDB();
	}
}

BOOL CEmailManagementDlg::ParsePathPieces(LPCTSTR szFile, LPTSTR szPath, LPTSTR szSkin)
{
	// Slice up the path a bit so that we have it in the required root/skin separation
	
    // Find the last \ character
    TCHAR* lastslash = (TCHAR *) _tcsrchr(szFile, _T('\\'));
    if (lastslash) {
		
        // Null it out, then get the next \ so that we have the end of the path
        *lastslash = 0;
		
        TCHAR* pathend = (TCHAR *) _tcsrchr(szFile, _T('\\'));
        if (pathend) {
			
            // Copy path, length is pathend minus pathstart
            // (we leave off the trailing \, it works either way)
            _tcsncpy(szPath, szFile, pathend - szFile);
			
            // Copy the rest, not forgetting to put the \ back
            *lastslash = _T('\\');
            _tcscpy(szSkin, pathend + 1);
            return TRUE;
        }
    }
	
    return FALSE;
}

void CEmailManagementDlg::OnDestroy() 
{
	UnSubclassControls();
	
	CDialog::OnDestroy();
}

void CEmailManagementDlg::UnSubclassControls()
{
	SETNOSKINHWND(m_listBlack);
	SETNOSKINHWND(m_listContact);
	SETNOSKINHWND(m_listFujian);
	SETNOSKINHWND(m_listGroup);
	SETNOSKINHWND(m_listRecord);
	SETNOSKINHWND(m_listRecycleBin);
	SETNOSKINHWND(m_listType);
	/*SETNOSKINHWND(m_Slider1);
	SETNOSKINHWND(m_Slider2);
	SETNOSKINHWND(m_Slider3);
	SETNOSKINHWND(m_Slider4);
	SETNOSKINHWND(m_Slider5);
	SETNOSKINHWND(m_Slider6);*/
}

void CEmailManagementDlg::OnChangeMySkin() 
{
	TCHAR szFile[MAX_PATH] = {0};
	OPENFILENAME OpenFileName;
	
	OpenFileName.lStructSize       = sizeof(OPENFILENAME);
	OpenFileName.hwndOwner         = m_hWnd;
	OpenFileName.hInstance         = AfxGetInstanceHandle();
	OpenFileName.lpstrFilter       = _T("Skin++ skinfiles (*.ssk)\0*.ssk\0\0");
	OpenFileName.lpstrCustomFilter = NULL;
	OpenFileName.nMaxCustFilter    = 0;
	OpenFileName.nFilterIndex      = 0;
	OpenFileName.lpstrFile         = szFile;
	OpenFileName.nMaxFile          = sizeof(szFile);
	OpenFileName.lpstrFileTitle    = NULL;
	OpenFileName.nMaxFileTitle     = 0;
	OpenFileName.lpstrInitialDir   = _T("..\\skins");
	OpenFileName.lpstrTitle        = _T("Select a ssk File");
	OpenFileName.nFileOffset       = 0;
	OpenFileName.nFileExtension    = 0;
	OpenFileName.lpstrDefExt       = NULL;
	OpenFileName.Flags             = OFN_SHOWHELP | OFN_EXPLORER;
	
	if(GetOpenFileName(&OpenFileName))
	{
		TCHAR szPathA[MAX_PATH] = {0};
		TCHAR szPathB[MAX_PATH] = {0};
		
		// We need a root path and a skin directory/name combination
		ParsePathPieces(szFile, szPathA, szPathB);
		
		skinppLoadSkin(szFile);
		Invalidate();
	}	
}

void CEmailManagementDlg::OnRemoveSkin() 
{
	skinppRemoveSkin();	
}

//���û������л���ʱ���ʼ��
void CEmailManagementDlg::CurUserChangeInit()
{
	if(m_strCurUser!="")
	{
		GetDlgItem(IDC_BTN_ADDTYPE)->EnableWindow(false);
		GetDlgItem(IDC_BTN_MODTYPE)->EnableWindow(false);
		GetDlgItem(IDC_BTN_DELTYPE)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BTN_ADDTYPE)->EnableWindow(true);
		GetDlgItem(IDC_BTN_MODTYPE)->EnableWindow(true);
		GetDlgItem(IDC_BTN_DELTYPE)->EnableWindow(true);
	}
	
	m_listContact.DeleteAllItems();
	m_listRecord.DeleteAllItems();
	m_listFujian.DeleteAllItems();
	m_listRecycleBin.DeleteAllItems();
	m_listBlack.DeleteAllItems();
	m_listGroup.DeleteAllItems();
	
	TRY
	{
		CString sql;
		for(int i=0;i<m_CurContactIdArr.GetSize();i++)
		{
			sql.Format("select * from contact_info_tab where contact_id=%d and is_black=0",m_CurContactIdArr.GetAt(i));
			InitContactListData(sql);
			//��ʼ��������
			sql.Format("select * from view_black_list where contact_id=%d",m_CurContactIdArr.GetAt(i));
			InitBlackListData(sql);
		}
		for(i=0;i<m_CurRecordIdArr.GetSize();i++)
		{
			sql.Format("select * from email_record_tab where record_id=%d and IS_RECYCLE_BIN=0",m_CurRecordIdArr.GetAt(i));
			InitEmailRecordInfo(sql);
		}
		for(i=0;i<m_CurRecordIdArr.GetSize();i++)
		{
			sql.Format("select * from email_record_tab where record_id=%d and IS_RECYCLE_BIN=1",m_CurRecordIdArr.GetAt(i));
			InitRecycleBinData(sql);
		}
		for(i=0;i<m_CurFujianIdArr.GetSize();i++)
		{
			sql.Format("select * from email_fujian where fid=%d",m_CurFujianIdArr.GetAt(i));
			InitFujianListData(sql);
		}
		for(i=0;i<m_CurGroupIdArr.GetSize();i++)
		{
			sql.Format("select * from contact_group where group_id=%d",m_CurGroupIdArr.GetAt(i));
			InitContactGroupData(sql);
		}
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

//�����û��ȼ���ʾ
void CEmailManagementDlg::SetUserTishi(CString name, CString rank)
{
	m_strUserTishi="��ǰ�û���"+name+" ";
	m_strUserTishi=m_strUserTishi+"�û��ȼ���"+rank;
}

void CEmailManagementDlg::OnLogOn() 
{
	CUserLogon dlg;
	int n=m_strCurUser.Find("@");
	CString temp=m_strCurUser.Left(n);
	dlg.m_strUserName=temp;
	if(IDOK==dlg.DoModal())
	{
		if(""==dlg.m_strPasswd)
		{
			MessageBox("�û������벻����Ϊ�գ�","����");
			return;
		}
		if(""==dlg.m_strUserName && "955219"==dlg.m_strPasswd)
		{
			UpdateData(true);
			MessageBox("���Ѿ��л��������Ȩ���û��������ز�����");
			SetUserTishi("���ܵĹ���Ա","super vip");
			m_strCurUser="";
			ClearAllLists();
			InitListData();
			UpdateData(false);
		}
		else
		{
			TRY
			{
				CRecordset rs;
				rs.m_pDatabase=&m_db;
				CString sql;
				
				sql.Format("select * from email_user where user_name='%s'",dlg.m_strUserName+userNameTear);
				rs.Open(CRecordset::dynaset,sql);
				CString userPassWd,userName;
				
				while(!rs.IsEOF())
				{
					userPassWd="";userName="";
					
					rs.GetFieldValue(1,userName);
					rs.GetFieldValue(2,userPassWd);
					
					//�Ѽ�¼���뵽����վ�б�ؼ���
					//ReadBlackListInfo(blackID,blackName,blackEmail);
					rs.MoveNext();
				}
				rs.Close();
				
				if(userPassWd==dlg.m_strPasswd && dlg.m_strPasswd!="")
				{
					UpdateData(true);
					m_strCurUser=dlg.m_strUserName+userNameTear;
					MessageBox("�û�"+dlg.m_strUserName+userNameTear+"���ã�"+"���Ѿ��ɹ�����½��");
					m_strUserTishi="��ǰ�û���"+m_strCurUser+" ";
					m_strUserTishi=m_strUserTishi+"�û��ȼ���"+GetCurUserRank();
					GetCurUserIdInfo();
					CurUserChangeInit();
					UpdateData(false);
				}
				if(userName=="")
				{
					MessageBox("�û���¼���ɹ�!");
				}
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
	}
}


void CEmailManagementDlg::GetCurUserIdInfo()
{
	m_CurContactIdArr.RemoveAll();
	m_CurFujianIdArr.RemoveAll();
	m_CurRecordIdArr.RemoveAll();
	m_CurGroupIdArr.RemoveAll();
	
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		sql.Format("select * from user_own where user_id=%d",GetCurUserID());
		rs.Open(CRecordset::dynaset,sql);
		
		int contactID,recordID,fujianID,groupID;
		
		while(!rs.IsEOF())
		{
			contactID=-1;	recordID=-1;	fujianID=-1;	groupID=-1;
			
			CDBVariant var;
			rs.GetFieldValue((short)1,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				contactID=var.m_iVal;
			}
			var.Clear();
			rs.GetFieldValue(2,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				recordID=var.m_iVal;
			}
			var.Clear();
			rs.GetFieldValue(4,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				fujianID=var.m_iVal;
			}
			var.Clear();
			rs.GetFieldValue(3,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				groupID=var.m_iVal;
			}
			var.Clear();
			if(contactID>0 && !isInArr(contactID,&m_CurContactIdArr))
			{
				m_CurContactIdArr.Add(contactID);
			}
			if(fujianID>0 && !isInArr(fujianID,&m_CurFujianIdArr))
			{
				m_CurFujianIdArr.Add(fujianID);
			}
			if(recordID>0 && !isInArr(recordID,&m_CurRecordIdArr))
			{
				m_CurRecordIdArr.Add(recordID);
			}
			if(groupID>0 && !isInArr(groupID,&m_CurGroupIdArr))
			{
				m_CurGroupIdArr.Add(groupID);
			}
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

//��õ�ǰ�û��ĵȼ�
CString CEmailManagementDlg::GetCurUserRank()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		sql.Format("select count(record_id) from user_own where user_id=%d and record_id>0",GetCurUserID());
		rs.Open(CRecordset::dynaset,sql);
		
		int count;
		
		while(!rs.IsEOF())
		{
			count=-1;
			CDBVariant var;
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				count=var.m_iVal;
			}
			var.Clear();
			rs.MoveNext();
		}
		rs.Close();
		
		CString strCount;
		strCount.Format("%d",count);
		return strCount;
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
		return "0";
}

//��ȡ��ǰ�û���id
int CEmailManagementDlg::GetCurUserID()
{
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		sql.Format("select * from Email_user where user_name='%s'",m_strCurUser);
		rs.Open(CRecordset::dynaset,sql);
		
		int userID;
		
		while(!rs.IsEOF())
		{
			userID=-1;
			CDBVariant var;
			rs.GetFieldValue((short)0,var,SQL_C_SLONG);
			if(var.m_dwType!=DBVT_NULL)
			{
				userID=var.m_iVal;
			}
			var.Clear();
			rs.MoveNext();
		}
		rs.Close();
		return userID;
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
		return -1;
}

BOOL CEmailManagementDlg::isInArr(int a, CArray<int,int> *arr)
{
	for(int i=0;i<arr->GetSize();i++)
	{
		if(a==arr->GetAt(i))
		{
			return TRUE;
		}
	}
	if(i==arr->GetSize())
	{
		return FALSE;
	}
	return FALSE;
}

void CEmailManagementDlg::OnUserRegist() 
{
	CUserRegistDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.m_strPassword == dlg.m_strOKPassword && dlg.m_strUserName!="" && dlg.m_strPassword!="" && dlg.m_strOKPassword!="")
		{
			TRY
			{
				//�򿪼�¼��
				CRecordset rs(&m_db);
				rs.Open(CRecordset::dynaset,"select max(user_id) from email_user");
				
				//��������Ӽ�¼���û���IDֵ
				int newUserID=1;
				//������ݿ������м�¼�ˣ����µ��û�ID=�û���ID���ֵ��1
				if(!rs.IsEOF())
				{
					CDBVariant var;
					rs.GetFieldValue((short)0,var,SQL_C_SLONG);
					if(var.m_dwType!=DBVT_NULL)
					{
						newUserID=var.m_iVal+1;
					}
				}
				rs.Close();
				
				//�����������û���¼���ַ���
				CString sql;
				sql.Format("insert into email_user values(%d,'%s','%s')",\
					newUserID,dlg.m_strUserName+userNameTear,dlg.m_strOKPassword);
				TRACE(sql);
				//�µ��û���¼���뵽���ݿ���
				m_db.ExecuteSQL(sql);
				ClearAllListsUnless();
				UpdateData(true);
				m_strCurUser=dlg.m_strUserName+userNameTear;
				SetUserTishi(m_strCurUser,"0");
				UpdateData(false);
			}
			CATCH(CDBException,ex)
			{
				AfxMessageBox(ex->m_strError);
				AfxMessageBox(ex->m_strStateNativeOrigin);
			}
			AND_CATCH(CException,e)
			{
				TCHAR szError[100];
				e->GetErrorMessage(szError,100);
				AfxMessageBox(szError);
			}
			END_CATCH;
		}
	}
	else
	{
		MessageBox("�û������벻��Ϊ�գ��������ȷ������Ҫһ�£�","����");
	}
}

//�鿴���е��û�
void CEmailManagementDlg::OnAllUsers() 
{
	if(m_strCurUser!="")
	{
		MessageBox("��ͨ�û�û�д���Ȩ��");
		return;
	}
	else
	{
		CAllUsersDlg dlg;
		dlg.DoModal();
	}
}

//���һ�У�����ϵͳ��Ĭ�ϳ���򿪸���
void CEmailManagementDlg::OnClickListFujian(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	POSITION Pos = m_listFujian.GetFirstSelectedItemPosition();
    int nSelect = -1;
    while ( Pos )
    {
        nSelect = m_listFujian.GetNextSelectedItem(Pos);    //nSelect�ܻ�õڼ���
    }
	char szFirstTrunk[60] = { 0 };
    m_listFujian.GetItemText(nSelect,1, szFirstTrunk, 60);  //�����Ҫ����ֵ��szFirstTrunk*/
	CString cmd;
	if("txt"==GetSuffix(szFirstTrunk))
	{
		cmd="notepad.exe  ";
	}
    else if("bmp"==GetSuffix(szFirstTrunk) || "png"==GetSuffix(szFirstTrunk) ||"jpg"==GetSuffix(szFirstTrunk)
		|| "jpeg"==GetSuffix(szFirstTrunk))
	{
		cmd="mspaint.exe  ";
	}
	else if("doc"==GetSuffix(szFirstTrunk))
	{
		cmd="E:\\Users\\dell\\AppData\\Local\\Kingsoft\\WPS Office\\ksolaunch.exe ";
	}
	else if("avi"==GetSuffix(szFirstTrunk) || "mp4"==GetSuffix(szFirstTrunk) )
	{
		cmd="wmplayer.exe ";
	}
	cmd+=dir;
	cmd+=szFirstTrunk;
	WinExec(cmd, SW_SHOW);
	
	*pResult = 0;
}

//�鿴�ռ���
void CEmailManagementDlg::OnBtnReceiveBin() 
{
	m_listRecord.DeleteAllItems();
	TRY
	{
		CRecordset rs;
		rs.m_pDatabase=&m_db;
		CString sql;
		
		//���ʼ���¼�б�ؼ�������ʼ�������Ϣ
		sql.Format("select * from email_record_tab where (IS_RECYCLE_BIN=0 or IS_RECYCLE_BIN is null)\
			and contact_id in(select contact_id from contact_info_tab where contact_name='%s')",m_strCurUser);
		//��ȡ�ʼ����͵ļ�¼��
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
			
			CRecordset rs2(&m_db);
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
			ReadRecordInfo(recordID,strName,sendDate,isFujian,strType,emailTxt,fujianName);
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

//�鿴������
void CEmailManagementDlg::OnBtnSendBin() 
{
	GetCurUserIdInfo();
	CurUserChangeInit();
}


//����ļ�����չ��
CString CEmailManagementDlg::GetSuffix(CString strFileName)
{
	return strFileName.Right(strFileName.GetLength()-strFileName.ReverseFind('.')-1);
}

//��ָ�����б�ؼ�ȡ������
void CEmailManagementDlg::CancelListHigh(CListCtrl m_list)
{
	for(int i=0;i<m_listRecord.GetItemCount();i++)
	{
		m_list.SetItemState(i, 0,-1);
	}
}

//�ʼ���¼��ģ����ѯ
void CEmailManagementDlg::OnBtnBlurFind() 
{
	CBlurFindDlg dlg;
	if(IDOK==dlg.DoModal())
	{
		int option;
		option=dlg.m_nRecordBlurFindOption;
		CString sql;
		CString sk1,sk2,sk3;
		
		if(0==option)
		{
			sk1="%"+dlg.m_strKeyName+"%";
			sk2="%"+dlg.m_strKeyName;
			sk3=dlg.m_strKeyName+"%";
			
			sql.Format("select record_id from email_record_tab where contact_id in (select \
																							 contact_id from contact_info_tab where contact_name like '%s' or\
																							 contact_name like '%s'or \
																							 contact_name like '%s')",sk1,sk2,sk3);
		}
		else if(1==option)
		{
			sk1="%"+dlg.m_strKeyEmail+"%";
			sk2="%"+dlg.m_strKeyEmail;
			sk3=dlg.m_strKeyEmail+"%";
			
			sql.Format("select record_id from email_record_tab where contact_id in (select \
																							 contact_id from contact_info_tab where e_mail like '%s' or\
																							 contact_name like '%s'or \
																							 contact_name like '%s')",sk1,sk2,sk3);
		}
		else
		{
			MessageBox("���������룬������","��ʾ");
		}
		TRY
		{
			CRecordset rs(&m_db);
			rs.Open(CRecordset::dynaset,sql);
			
			int recordID=-1;
			
			for(int i=0;i<m_listRecord.GetItemCount();i++)
			{
				this->m_listRecord.SetItemState(i, 0,-1);
			}
			
			while(!rs.IsEOF())
			{
				CDBVariant var;
				//��ȡidֵ
				rs.GetFieldValue((short)0,var,SQL_C_SLONG);
				if(var.m_dwType!=DBVT_NULL)
				{
					recordID=var.m_iVal;
				}
				var.Clear();
				
				//λѡ�������Ԫ�������ɫ
				for(int nItem=0;nItem<m_listRecord.GetItemCount();nItem++)
				{
					CString strID,strListID;
					strID.Format("%d",recordID);
					strListID=m_listRecord.GetItemText(nItem,0);
					if(strID==strListID)
					{
						m_listRecord.SetFocus();
						m_listRecord.SetItemState(nItem,LVIS_SELECTED,LVIS_SELECTED);
					}
				}
				
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
}

//ͨ�����緢���ʼ�
void CEmailManagementDlg::OnNetSendMail() 
{
	CMyEmailSendDlg dlg;
	CString strEmailTo="18186482897@163.com";
	CString strMyContents="Hello World, Hello Email! hello DB";
	CString strEmailContents="From: \"lucy\"<wxbliaotian@163.com>\r\n"
			"To: \"dasiy\"<"+strEmailTo+">\r\n"
			"Subject: Hello\r\n\r\n"
			+strMyContents;
    dlg.m_strReceiveAddress=strEmailTo;
	dlg.m_strMyInfo=strMyContents;
	if(IDOK==dlg.DoModal())
	{
		strEmailTo=dlg.m_strReceiveAddress;
		strMyContents=dlg.m_strMyInfo;
		strEmailContents="From: \"lucy\"<wxbliaotian@163.com>\r\n"
			"To: \"dasiy\"<"+strEmailTo+">\r\n"
			"Subject: Hello\r\n\r\n"
			+strMyContents;
		char* EmailTo=(LPSTR)(LPCTSTR)strEmailTo;
		char* EmailContents=(LPSTR)(LPCTSTR)strEmailContents;
		SendMail(EmailTo,EmailContents);
	}	
}

void CEmailManagementDlg::OnBtnDraft() 
{
	CEmailDraftDlg dlg;
	if(dlg.DoModal())
	{

	}
}

//ע����ǰ�û�
void CEmailManagementDlg::OnUserCancellation() 
{
	if(m_strCurUser!="")
	{
		CString sql;
		sql.Format("call user_delete(%d)",GetCurUserID());
		MyExecuteSQL(sql);
		InitListData();
		MessageBox("��ǰ�û��Ѿ�ע����ллʹ�ã�");
	}
	else
	{
		MessageBox("��ǰ�ǳ����û�������ɾ����");
	}
}
