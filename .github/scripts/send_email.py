#!/usr/bin/env python3
import os
import sys
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email import encoders
from datetime import datetime


def debug(msg):
    print(f"[DEBUG {datetime.utcnow().isoformat()}] {msg}", file=sys.stderr)


def main():
    try:
        # 打印环境变量
        debug("开始读取环境变量...")
        env_vars = {
            "SMTP_HOST": os.getenv("SMTP_HOST"),
            "SMTP_PORT": os.getenv("SMTP_PORT"),
            "SMTP_USER": os.getenv("SMTP_USER"),
            "EMAIL_FROM": os.getenv("EMAIL_FROM"),
            "EMAIL_TO": os.getenv("EMAIL_TO"),
        }
        for k, v in env_vars.items():
            debug(f"{k} = {v}")

        # 计算昨天的文件名
        debug("计算文件名...")
        yesterday = os.popen("TZ=Asia/Shanghai date -d 'yesterday' '+%Y-%m-%d'").read().strip()
        filename = f"{yesterday}.md"
        debug(f"期待的附件文件：{filename}")

        # 检查文件是否存在
        if not os.path.isfile(filename):
            debug(f"ERROR: 附件文件不存在：{filename}")
            sys.exit(1)

        # 读取 Markdown 附件
        debug(f"打开并读取文件：{filename}")
        with open(filename, 'rb') as f:
            file_data = f.read()
        debug(f"读取文件大小：{len(file_data)} 字节")

        # 构造邮件
        debug("开始构造邮件对象...")
        msg = MIMEMultipart()
        msg['Subject'] = f"每日提交摘要 — {yesterday}"
        msg['From'] = os.environ['EMAIL_FROM']
        msg['To'] = os.environ['EMAIL_TO']

        # 邮件正文
        body = MIMEText(f"请查收 {filename}，提交摘要见附件。", _subtype='plain', _charset='utf-8')
        msg.attach(body)

        # 添加附件
        debug("附加文件到邮件...")
        part = MIMEBase('application', 'octet-stream')
        part.set_payload(file_data)
        encoders.encode_base64(part)
        part.add_header('Content-Disposition', f'attachment; filename="{filename}"')
        msg.attach(part)

        # 发送邮件
        debug("连接 SMTP 服务器...")
        server = smtplib.SMTP(env_vars["SMTP_HOST"], int(env_vars["SMTP_PORT"]))
        debug("启动 TLS...")
        server.starttls()
        debug("登录 SMTP...")
        server.login(os.environ['SMTP_USER'], os.environ['SMTP_PASSWORD'])
        debug("发送邮件...")
        server.send_message(msg)
        debug("邮件发送成功。")
        server.quit()
    except Exception as e:
        debug(f"邮件发送失败，异常信息：{e}")
        # 打印完整堆栈
        import traceback

        traceback.print_exc(file=sys.stderr)
        sys.exit(1)

if __name__ == '__main__':
    main()
