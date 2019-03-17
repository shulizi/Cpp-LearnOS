DELIMITER //
create procedure 
void ChangeDNO()
{

    
    int maxage;
    char xh[7], xm[9], sex[3], yxh[4], newdno[4];
    EXEC SQL END DECLARE SECTION;

    scanf("%d",&maxage);
    EXEC SQL OPEN ex;
    while (1)
    {
        if (SQLCA.SQLSTATE ! ='00000')
            break;
        printf("%s,%s, %s,%s", :eno, :ename, :sex, :yxh);
        printf("UPDATE DNO? ");
        scanf("%c", &yn);
        if (yn=='y' or yn='Y')
        { printf("INPUT NEW DNO: ");
            scanf("%s", newdno);
            
            
        }
    }
    EXEC SQL CLOSE ex;
}
