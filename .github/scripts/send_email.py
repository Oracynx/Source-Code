#!/usr/bin/env python3
import os
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders

def main():
    # 准备文件名
    yesterday = os.popen("TZ=Asia/Shanghai date -d 'yesterday' '+%Y-%m-%d'").read().strip()
    filename = f"{yesterday}.md"

    # 读取 Markdown 附件
    with open(filename, 'rb') as f:
        file_data = f.read()

    # 构造邮件
    msg = MIMEMultipart()
    msg['Subject'] = f"每日提交摘要 — {yesterday}"
    msg['From'] = os.environ['EMAIL_FROM']
    msg['To'] = os.environ['EMAIL_TO']

    # 邮件正文
    body = MIMEText(f"请查收 {filename}，提交摘要见附件。", _subtype='plain', _charset='utf-8')
    msg.attach(body)

    # 添加附件
    part = MIMEBase('application', 'octet-stream')
    part.set_payload(file_data)
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', f'attachment; filename="{filename}"')
    msg.attach(part)

    # 发送邮件
    server = smtplib.SMTP(os.environ['SMTP_HOST'], int(os.environ['SMTP_PORT']))
    server.starttls()
    server.login(os.environ['SMTP_USER'], os.environ['SMTP_PASSWORD'])
    server.send_message(msg)
    server.quit()

if __name__ == '__main__':
    main()
